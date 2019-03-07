//
// Created by FLXR on 7/6/2018.
//

#include <GL/glew.h>
#include "glbaseshader.hpp"
#include "glcommon.hpp"
#include "glshadersampler.hpp"
#include <xe/utils/assert.hpp>

namespace xe { namespace internal {

	GLBaseShader::GLBaseShader(const string &name, const std::vector<ShaderFile *> &shaderPipeline) :
			name(name),
			handle(0) {

		uniformBuffers.push_back(new GLShaderUniformBuffer("GLOBAL"));

		glCall(handle = glCreateProgram());

		for (const auto &s : shaderPipeline) {
			ShaderType type = s->getType();
			sources.emplace(type, s->getRawSource());

			shaders[type] = s->compile();
			if (!shaders[type]) {
				glCall(glDeleteProgram(handle));
				XE_CORE_FATAL("[GLBaseShader]: shader name: '", name, "'");
				XE_ASSERT(false);
			}
			s->parse(uniformBuffers, samplers, structs);

			glCall(glAttachShader(handle, shaders[type]));
		}

		glCall(glLinkProgram(handle));
		glCall(glValidateProgram(handle));

		resolveUniforms();

		//cleanup
		for (const auto &s : shaderPipeline) {
			ShaderType type = s->getType();
			glCall(glDetachShader(handle, shaders[type]));
			delete s;
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

	void GLBaseShader::setSourceConstant(ShaderType type, const string &valueName, const string &value) const {
		auto &&it = sources.find(type);
		if (it == sources.end()) {
			XE_CORE_ERROR("[GLBaseShader]: '", name, "' doesn't have ", shaderTypeToString(type), " attachment!");
			return;
		}

		string src = it->second;
		replaceAll(src, valueName, value);

		ShaderFile *sf = ShaderFile::fromPreparedSource(type, src);

		uint id = sf->compile();
		if (!id) {
			XE_CORE_ERROR("[GLBaseShader]: failed to set constant '", valueName, "' to shader '", name, "'");
			return;
		}

		shaders[type] = id;

		for (auto &&s : shaders) {
			glCall(glAttachShader(handle, s.second));
		}

		glCall(glLinkProgram(handle));
		glCall(glValidateProgram(handle));

		for (auto &&s : shaders) {
			glCall(glDetachShader(handle, s.second));
		}

		delete sf;
	}

	void GLBaseShader::bind() const {
		glCall(glUseProgram(handle));
	}

	void GLBaseShader::unbind() const {
#ifdef XE_DEBUG
		glCall(glUseProgram(0));
#endif
	}

	void GLBaseShader::setUniformBuffer(byte *data, uint size, uint slot) const {
		bind();
		XE_ASSERT(uniformBuffers.size() > slot);
		resolveAndSetUniforms(uniformBuffers[slot], data, size);
	}

	void GLBaseShader::bindUniformBlock(const char *blockName, uint location) const {
		glCall(uint index = glGetUniformBlockIndex(handle, blockName));
		glCall(glUniformBlockBinding(handle, index, location));
	}

	void GLBaseShader::resolveAndSetUniformField(const GLShaderUniform &field, byte *data, int32 offset) const {
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
			case GLShaderUniform::Type::Image2D: setUniform1i(field.getLocation(), *(int32 *) &data[offset]);
				break;
			case GLShaderUniform::Type::Image3D: setUniform1i(field.getLocation(), *(int32 *) &data[offset]);
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
						field->location = getUniformLocation(uniform->name + "." + field->name, false);
					}
				} else {
					uniform->location = getUniformLocation(uniform->name, false);
				}
			}
		}

		uint sampler = 0;
		for (auto &smpl : samplers) {
			GLShaderSampler *resource = (GLShaderSampler *) smpl;

			const uint location = getUniformLocation(resource->name, false);
			if (resource->count == 1) {
				resource->location = sampler;
				setUniform1i(location, sampler++);

			} else if (resource->count > 1) {
				resource->location = 0;

				const uint count = resource->count;
				int32 samplers[count];

				for (uint s = 0; s < count; s++) {
					samplers[s] = s;
				}

				setUniform1iv(resource->getName(), samplers, count);
			}
		}

		glCall(glUseProgram(0));
	}

	uint GLBaseShader::getUniformLocation(const string &name, bool runTime) const {
		glCall(GLint result = glGetUniformLocation(handle, name.c_str()));
		if (result == -1) {
			if (runTime) {
				XE_CORE_ERROR("[GLBaseShader]: '", GLBaseShader::name, "' could not get uniform location '", name, "'");
			} else {
				XE_CORE_WARN("[GLBaseShader]: '", GLBaseShader::name, "' uniform '", name, "' optimized out");
			}
		}

		return static_cast<uint>(result);
	}

	ShaderUniform *GLBaseShader::findUniform(const string &name, const ShaderUniformBuffer *buff) {
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

	void GLBaseShader::resolveAndSetUniforms(ShaderUniformBuffer *buffer, byte *data, uint size) const {
		const ShaderUniformVec &uniforms = buffer->getUniforms();
		for (auto &&uniform : uniforms) {
			resolveAndSetUniform((GLShaderUniform *) uniform, data, size);
		}
	}

	void
	GLBaseShader::resolveAndSetUniform(GLShaderUniform *uniform, byte *data, uint size) const {
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
			case GLShaderUniform::Type::Image2D: setUniform1i(uniform->getLocation(), *(int32 *) &data[offset]);
				break;
			case GLShaderUniform::Type::Image3D: setUniform1i(uniform->getLocation(), *(int32 *) &data[offset]);
				break;
			case GLShaderUniform::Type::Struct: setUniformStruct(uniform, data, offset);
				break;
			default: XE_ASSERT(false, "Unknown type!");
		}
	}

	void
	GLBaseShader::setUniformStruct(const GLShaderUniform *uniform, byte *data, int32 offset) const {
		const ShaderStruct &s = uniform->getShaderUniformStruct();
		const auto &fields = s.getFields();

		for (auto &&field : fields) {
			auto &&f = (GLShaderUniform *) field;

			resolveAndSetUniformField(*f, data, offset);
			offset += field->getSize();
		}
	}

	void GLBaseShader::setUniform1f(const string &name, float value) const {
		setUniform1f(getUniformLocation(name), value);
	}

	void GLBaseShader::setUniform1fv(const string &name, float *value, int32 count) const {
		setUniform1fv(getUniformLocation(name), value, count);
	}

	void GLBaseShader::setUniform1i(const string &name, int32 value) const {
		setUniform1i(getUniformLocation(name), value);
	}

	void GLBaseShader::setUniform1iv(const string &name, int32 *value, int32 count) const {
		setUniform1iv(getUniformLocation(name), value, count);
	}

	void GLBaseShader::setUniform2f(const string &name, const vec2 &vector) const {
		setUniform2f(getUniformLocation(name), vector);
	}

	void GLBaseShader::setUniform3f(const string &name, const vec3 &vector) const {
		setUniform3f(getUniformLocation(name), vector);
	}

	void GLBaseShader::setUniform4f(const string &name, const vec4 &vector) const {
		setUniform4f(getUniformLocation(name), vector);
	}

	void GLBaseShader::setUniformMat4(const string &name, const mat4 &matrix) const {
		setUniformMat4(getUniformLocation(name), matrix);
	}

	void GLBaseShader::setUniform1f(int32 location, float value) const {
		glCall(glUniform1f(location, value));
	}

	void GLBaseShader::setUniform1fv(int32 location, float *value, int32 count) const {
		glCall(glUniform1fv(location, count, value));
	}

	void GLBaseShader::setUniform1i(int32 location, int32 value) const {
		glCall(glUniform1i(location, value));
	}

	void GLBaseShader::setUniform1iv(int32 location, int32 *value, int32 count) const {
		glCall(glUniform1iv(location, count, value));
	}

	void GLBaseShader::setUniform2f(int32 location, const vec2 &vector) const {
		glCall(glUniform2f(location, vector.x, vector.y));
	}

	void GLBaseShader::setUniform3f(int32 location, const vec3 &vector) const {
		glCall(glUniform3f(location, vector.x, vector.y, vector.z));
	}

	void GLBaseShader::setUniform4f(int32 location, const vec4 &vector) const {
		glCall(glUniform4f(location, vector.x, vector.y, vector.z, vector.w));
	}

	void GLBaseShader::setUniformMat4(int32 location, const mat4 &matrix) const {
		glCall(glUniformMatrix4fv(location, 1, GL_TRUE, matrix.elements));
	}

}}