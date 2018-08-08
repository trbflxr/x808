//
// Created by FLXR on 7/6/2018.
//

#include "glshader.hpp"
#include "glcommon.hpp"
#include "utils/log.hpp"

namespace xe { namespace api {

	GLShader::GLShader(const std::string_view &name, const std::vector<ShaderFile *> &shaderPipeline) :
			Shader(name) {

		uniformBuffers.push_back(new api::GLShaderUniformBuffer("GLOBAL"));

		glCall(handle = glCreateProgram());

		uint shaders[shaderPipeline.size()];

		for (uint i = 0; i < shaderPipeline.size(); ++i) {
			shaders[i] = shaderPipeline[i]->compile();
			if (!shaders[i]) {
				glCall(glDeleteProgram(handle));
				XE_FATAL("[GLShader]: ", name);
				XE_ASSERT(false);
			}
			shaderPipeline[i]->parse(uniformBuffers, resources, structs);

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

	GLShader::~GLShader() {
		glCall(glDeleteProgram(handle));
	}

	void GLShader::bind() const {
		glCall(glUseProgram(handle));
	}

	void GLShader::unbind() const {
		glCall(glUseProgram(0));
	}

	void GLShader::setUniformBuffer(byte *data, uint size, uint slot) {
		bind();
		XE_ASSERT(uniformBuffers.size() > slot);
		resolveAndSetUniforms(uniformBuffers[slot], data, size);
	}

	void GLShader::setUniform(const std::string_view &name, byte *data) {
		ShaderUniform *uniform = findUniform(name);
		if (!uniform) {
			XE_ERROR("Cannot find uniform in ", name, " shader with shaderName '", GLShader::name, "'");
			return;
		}
		resolveAndSetUniform((GLShaderUniform *) uniform, data, 0);
	}

	void GLShader::resolveAndSetUniformField(const GLShaderUniform &field, byte *data, int32 offset) {
		switch (field.getType()) {
			case GLShaderUniform::Type::FLOAT32: setUniform1f(field.getLocation(), *(float *) &data[offset]);
				break;
			case GLShaderUniform::Type::INT32: setUniform1i(field.getLocation(), *(int32 *) &data[offset]);
				break;
			case GLShaderUniform::Type::VEC2: setUniform2f(field.getLocation(), *(vec2 *) &data[offset]);
				break;
			case GLShaderUniform::Type::VEC3: setUniform3f(field.getLocation(), *(vec3 *) &data[offset]);
				break;
			case GLShaderUniform::Type::VEC4: setUniform4f(field.getLocation(), *(vec4 *) &data[offset]);
				break;
			case GLShaderUniform::Type::MAT4: setUniformMat4(field.getLocation(), *(mat4 *) &data[offset]);
				break;
			default: XE_ASSERT(false, "Unknown type!");
		}
	}

	void GLShader::resolveUniforms() {
		bind();

		for (auto &&buffer : uniformBuffers) {
			GLShaderUniformBuffer *decl = (GLShaderUniformBuffer *) buffer;

			for (auto &&u : decl->getUniforms()) {
				GLShaderUniform *uniform = (GLShaderUniform *) u;

				if (uniform->getType() == GLShaderUniform::Type::STRUCT) {
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
		for (auto &res : resources) {
			GLShaderResource *resource = (GLShaderResource *) res;

			uint location = getUniformLocation(resource->name);
			if (resource->count == 1) {
				resource->register_ = sampler;
				setUniform1i(location, sampler++);

			} else if (resource->count > 1) {
				resource->register_ = 0;

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

	uint GLShader::getUniformLocation(const std::string_view &name) {
		glCall(GLint result = glGetUniformLocation(handle, name.data()));
		if (result == -1) {
			XE_ERROR("[GLShader]: name: '", GLShader::name, "' could not find uniform '", name, "'");
		}

		return static_cast<uint>(result);
	}

	ShaderUniform *GLShader::findUniform(const std::string_view &name,
	                                     const ShaderUniformBuffer *buff) {
		for (auto &&uniform : buff->getUniforms()) {
			if (uniform->getName() == name) return uniform;
		}
		return nullptr;
	}

	ShaderUniform *GLShader::findUniform(const std::string_view &name) {
		ShaderUniform *result = nullptr;

		for (auto &&buffer : uniformBuffers) {
			result = findUniform(name, buffer);
			if (result) return result;
		}

		return result;
	}

	void GLShader::resolveAndSetUniforms(ShaderUniformBuffer *buffer, byte *data, uint size) {
		const ShaderUniformVec &uniforms = buffer->getUniforms();
		for (auto &&uniform : uniforms) {
			resolveAndSetUniform((GLShaderUniform *) uniform, data, size);
		}
	}

	void
	GLShader::resolveAndSetUniform(GLShaderUniform *uniform, byte *data, uint size) {
		if (uniform->getLocation() == -1) return;

		uint offset = uniform->getOffset();
		switch (uniform->getType()) {
			case GLShaderUniform::Type::FLOAT32: setUniform1f(uniform->getLocation(), *(float *) &data[offset]);
				break;
			case GLShaderUniform::Type::INT32: setUniform1i(uniform->getLocation(), *(int32 *) &data[offset]);
				break;
			case GLShaderUniform::Type::VEC2: setUniform2f(uniform->getLocation(), *(vec2 *) &data[offset]);
				break;
			case GLShaderUniform::Type::VEC3: setUniform3f(uniform->getLocation(), *(vec3 *) &data[offset]);
				break;
			case GLShaderUniform::Type::VEC4: setUniform4f(uniform->getLocation(), *(vec4 *) &data[offset]);
				break;
			case GLShaderUniform::Type::MAT4: setUniformMat4(uniform->getLocation(), *(mat4 *) &data[offset]);
				break;
			case GLShaderUniform::Type::STRUCT: setUniformStruct(uniform, data, offset);
				break;
			default: XE_ASSERT(false, "Unknown type!");
		}
	}

	void
	GLShader::setUniformStruct(const GLShaderUniform *uniform, byte *data, int32 offset) {
		const ShaderStruct &s = uniform->getShaderUniformStruct();
		const auto &fields = s.getFields();

		for (auto &&field : fields) {
			auto &&f = (GLShaderUniform *) field;

			resolveAndSetUniformField(*f, data, offset);
			offset += field->getSize();
		}
	}

	void GLShader::setUniform1f(const std::string_view &name, float value) {
		setUniform1f(getUniformLocation(name), value);
	}

	void GLShader::setUniform1fv(const std::string_view &name, float *value, int32 count) {
		setUniform1fv(getUniformLocation(name), value, count);
	}

	void GLShader::setUniform1i(const std::string_view &name, int32 value) {
		setUniform1i(getUniformLocation(name), value);
	}

	void GLShader::setUniform1iv(const std::string_view &name, int32 *value, int32 count) {
		setUniform1iv(getUniformLocation(name), value, count);
	}

	void GLShader::setUniform2f(const std::string_view &name, const xe::vec2 &vector) {
		setUniform2f(getUniformLocation(name), vector);
	}

	void GLShader::setUniform3f(const std::string_view &name, const xe::vec3 &vector) {
		setUniform3f(getUniformLocation(name), vector);
	}

	void GLShader::setUniform4f(const std::string_view &name, const xe::vec4 &vector) {
		setUniform4f(getUniformLocation(name), vector);
	}

	void GLShader::setUniformMat4(const std::string_view &name, const xe::mat4 &matrix) {
		setUniformMat4(getUniformLocation(name), matrix);
	}

	void GLShader::setUniform1f(uint location, float value) {
		glCall(glUniform1f(location, value));
	}

	void GLShader::setUniform1fv(uint location, float *value, int32 count) {
		glCall(glUniform1fv(location, count, value));
	}

	void GLShader::setUniform1i(uint location, int32 value) {
		glCall(glUniform1i(location, value));
	}

	void GLShader::setUniform1iv(uint location, int32 *value, int32 count) {
		glCall(glUniform1iv(location, count, value));
	}

	void GLShader::setUniform2f(uint location, const xe::vec2 &vector) {
		glCall(glUniform2f(location, vector.x, vector.y));
	}

	void GLShader::setUniform3f(uint location, const xe::vec3 &vector) {
		glCall(glUniform3f(location, vector.x, vector.y, vector.z));
	}

	void GLShader::setUniform4f(uint location, const xe::vec4 &vector) {
		glCall(glUniform4f(location, vector.x, vector.y, vector.z, vector.w));
	}

	void GLShader::setUniformMat4(uint location, const xe::mat4 &matrix) {
		glCall(glUniformMatrix4fv(location, 1, GL_TRUE, matrix.elements));
	}

}}