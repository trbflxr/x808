//
// Created by FLXR on 7/6/2018.
//

#include "glbaseshader.hpp"
#include "glcommon.hpp"
#include "glshadersampler.hpp"

namespace xe { namespace internal {

	GLBaseShader::GLBaseShader(const string &name, const std::vector<ShaderFile *> &shaderPipeline) :
			name(name) {

		uniformBuffers.push_back(new GLShaderUniformBuffer("GLOBAL"));

		glCall(handle = glCreateProgram());

		uint shaders[shaderPipeline.size()];

		for (uint i = 0; i < shaderPipeline.size(); ++i) {
			shaders[i] = shaderPipeline[i]->compile();
			if (!shaders[i]) {
				glCall(glDeleteProgram(handle));
				XE_FATAL("[GLBaseShader]: shader name: ", name);
				XE_ASSERT(false);
				return;
			}
			shaderPipeline[i]->parse(uniformBuffers, samplers, structs);

			glCall(glAttachShader(handle, shaders[i]));
		}

		glCall(glLinkProgram(handle));
		glCall(glValidateProgram(handle));

		resolveUniforms();

		//cleanup
		for (uint i = 0; i < shaderPipeline.size(); ++i) {
			glCall(glDetachShader(handle, shaders[i]));
			glCall(glDeleteShader(shaders[i]));

			delete shaderPipeline[i];
		}
	}

	GLBaseShader::~GLBaseShader() {
		for (auto &&s : structs) {
			delete s;
		}
		for (auto &&s : samplers) {
			delete s;
		}
		for (auto &&u : uniformBuffers) {
			delete u;
		}
		glCall(glDeleteProgram(handle));
	}

	void GLBaseShader::bind() const {
		glCall(glUseProgram(handle));
	}

	void GLBaseShader::unbind() const {
		glCall(glUseProgram(0));
	}

	void GLBaseShader::setUniformBuffer(byte *data, uint size, uint slot) {
		bind();
		XE_ASSERT(uniformBuffers.size() > slot);
		resolveAndSetUniforms(uniformBuffers[slot], data, size);
	}

	void GLBaseShader::resolveAndSetUniformField(const GLShaderUniform &field, byte *data, int32 offset) {
		switch (field.getType()) {
			case GLShaderUniform::Type::Float32: setUniform1f(field.getLocation(), *(float *) &data[offset]);
				break;
			case GLShaderUniform::Type::Int32: setUniform1i(field.getLocation(), *(int32 *) &data[offset]);
				break;
			case GLShaderUniform::Type::Vec2: setUniform2f(field.getLocation(), *(vec2 *) &data[offset]);
				break;
			case GLShaderUniform::Type::Vec3: setUniform3f(field.getLocation(), *(vec3 *) &data[offset]);
				break;
			case GLShaderUniform::Type::Vec4: setUniform4f(field.getLocation(), *(vec4 *) &data[offset]);
				break;
			case GLShaderUniform::Type::Mat4: setUniformMat4(field.getLocation(), *(mat4 *) &data[offset]);
				break;
			default: XE_ASSERT(false, "Unknown type!");
		}
	}

	void GLBaseShader::resolveUniforms() {
		bind();

		for (auto &&buffer : uniformBuffers) {
			GLShaderUniformBuffer *decl = (GLShaderUniformBuffer *) buffer;

			for (auto &&u : decl->getUniforms()) {
				GLShaderUniform *uniform = (GLShaderUniform *) u;

				if (uniform->getType() == GLShaderUniform::Type::Struct) {
					const ShaderStruct &s = uniform->getShaderUniformStruct();

					for (auto &&f : s.getFields()) {
						GLShaderUniform *field = (GLShaderUniform *) f;
						field->location = getUniformLocation(uniform->name + "." + field->name);
					}
				} else {
					uniform->location = getUniformLocation(uniform->name);
				}
			}
		}

		uint sampler = 0;
		for (auto &smpl : samplers) {
			GLShaderSampler *resource = (GLShaderSampler *) smpl;

			uint location = getUniformLocation(resource->name);
			if (resource->count == 1) {
				resource->location = sampler;
				setUniform1i(location, sampler++);

			} else if (resource->count > 1) {
				resource->location = 0;

				uint count = resource->count;
				int32 *samplers = new int32[count];

				for (uint s = 0; s < count; s++) {
					samplers[s] = s;
				}

				setUniform1iv(resource->getName(), samplers, count);
				delete[] samplers;
			}
		}

		unbind();
	}

	uint GLBaseShader::getUniformLocation(const string &name) {
		glCall(GLint result = glGetUniformLocation(handle, name.c_str()));
		if (result == -1) {
			XE_ERROR("[GLBaseShader]: name: '", GLBaseShader::name, "' could not find uniform '", name, "'");
		}

		return static_cast<uint>(result);
	}

	ShaderUniform *GLBaseShader::findUniform(const string &name,
	                                         const ShaderUniformBuffer *buff) {
		for (auto &&uniform : buff->getUniforms()) {
			if (uniform->getName() == name) return uniform;
		}
		return nullptr;
	}

	ShaderUniform *GLBaseShader::findUniform(const string &name) {
		ShaderUniform *result = nullptr;

		for (auto &&buffer : uniformBuffers) {
			result = findUniform(name, buffer);
			if (result) return result;
		}

		return result;
	}

	void GLBaseShader::resolveAndSetUniforms(ShaderUniformBuffer *buffer, byte *data, uint size) {
		const ShaderUniformVec &uniforms = buffer->getUniforms();
		for (auto &&uniform : uniforms) {
			resolveAndSetUniform((GLShaderUniform *) uniform, data, size);
		}
	}

	void
	GLBaseShader::resolveAndSetUniform(GLShaderUniform *uniform, byte *data, uint size) {
		if (uniform->getLocation() == -1) return;

		uint offset = uniform->getOffset();
		switch (uniform->getType()) {
			case GLShaderUniform::Type::Float32: setUniform1f(uniform->getLocation(), *(float *) &data[offset]);
				break;
			case GLShaderUniform::Type::Int32: setUniform1i(uniform->getLocation(), *(int32 *) &data[offset]);
				break;
			case GLShaderUniform::Type::Vec2: setUniform2f(uniform->getLocation(), *(vec2 *) &data[offset]);
				break;
			case GLShaderUniform::Type::Vec3: setUniform3f(uniform->getLocation(), *(vec3 *) &data[offset]);
				break;
			case GLShaderUniform::Type::Vec4: setUniform4f(uniform->getLocation(), *(vec4 *) &data[offset]);
				break;
			case GLShaderUniform::Type::Mat4: setUniformMat4(uniform->getLocation(), *(mat4 *) &data[offset]);
				break;
			case GLShaderUniform::Type::Struct: setUniformStruct(uniform, data, offset);
				break;
			default: XE_ASSERT(false, "Unknown type!");
		}
	}

	void
	GLBaseShader::setUniformStruct(const GLShaderUniform *uniform, byte *data, int32 offset) {
		const ShaderStruct &s = uniform->getShaderUniformStruct();
		const auto &fields = s.getFields();

		for (auto &&field : fields) {
			auto &&f = (GLShaderUniform *) field;

			resolveAndSetUniformField(*f, data, offset);
			offset += field->getSize();
		}
	}

	void GLBaseShader::setUniform1f(const string &name, float value) {
		setUniform1f(getUniformLocation(name), value);
	}

	void GLBaseShader::setUniform1fv(const string &name, float *value, int32 count) {
		setUniform1fv(getUniformLocation(name), value, count);
	}

	void GLBaseShader::setUniform1i(const string &name, int32 value) {
		setUniform1i(getUniformLocation(name), value);
	}

	void GLBaseShader::setUniform1iv(const string &name, int32 *value, int32 count) {
		setUniform1iv(getUniformLocation(name), value, count);
	}

	void GLBaseShader::setUniform2f(const string &name, const vec2 &vector) {
		setUniform2f(getUniformLocation(name), vector);
	}

	void GLBaseShader::setUniform3f(const string &name, const vec3 &vector) {
		setUniform3f(getUniformLocation(name), vector);
	}

	void GLBaseShader::setUniform4f(const string &name, const vec4 &vector) {
		setUniform4f(getUniformLocation(name), vector);
	}

	void GLBaseShader::setUniformMat4(const string &name, const mat4 &matrix) {
		setUniformMat4(getUniformLocation(name), matrix);
	}

	void GLBaseShader::setUniform1f(uint location, float value) {
		glCall(glUniform1f(location, value));
	}

	void GLBaseShader::setUniform1fv(uint location, float *value, int32 count) {
		glCall(glUniform1fv(location, count, value));
	}

	void GLBaseShader::setUniform1i(uint location, int32 value) {
		glCall(glUniform1i(location, value));
	}

	void GLBaseShader::setUniform1iv(uint location, int32 *value, int32 count) {
		glCall(glUniform1iv(location, count, value));
	}

	void GLBaseShader::setUniform2f(uint location, const vec2 &vector) {
		glCall(glUniform2f(location, vector.x, vector.y));
	}

	void GLBaseShader::setUniform3f(uint location, const vec3 &vector) {
		glCall(glUniform3f(location, vector.x, vector.y, vector.z));
	}

	void GLBaseShader::setUniform4f(uint location, const vec4 &vector) {
		glCall(glUniform4f(location, vector.x, vector.y, vector.z, vector.w));
	}

	void GLBaseShader::setUniformMat4(uint location, const mat4 &matrix) {
		glCall(glUniformMatrix4fv(location, 1, GL_TRUE, matrix.elements));
	}

}}