//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLBASESHADER_HPP
#define X808_GLBASESHADER_HPP


#include <xe/math/math.hpp>
#include <xe/resources/shaderfile.hpp>
#include <gfx/platform/platformbaseshader.hpp>
#include "glshaderuniform.hpp"

namespace xe { namespace internal {

	class GLBaseShader : public PlatformBaseShader {
	public:
		explicit GLBaseShader(const string &name, const std::vector<ShaderFile *> &shaderPipeline);
		~GLBaseShader() override;

		void bind() const override;
		void unbind() const override;

		void setUniformBuffer(byte *data, uint size, uint slot) const override;

		void bindUniformBlock(const char *blockName, uint location) const override;

		inline const ShaderUniformBufferVec &getUniforms() const override { return uniformBuffers; }
		inline const ShaderSamplerVec &getSamplers() const override { return samplers; }
		inline const string &getName() const override { return name; }
		inline uint getHandle() const override { return handle; }
		inline const std::unordered_map<string, string> &getSources() const override { return sources; }

	private:
		void resolveUniforms();
		uint getUniformLocation(const string &name, bool runTime = true) const;

		ShaderUniform *findUniform(const string &name, const ShaderUniformBuffer *buff);
		ShaderUniform *findUniform(const string &name);

		void resolveAndSetUniforms(ShaderUniformBuffer *buffer, byte *data, uint size) const;
		void resolveAndSetUniform(GLShaderUniform *uniform, byte *data, uint size) const;

		void resolveAndSetUniformField(const GLShaderUniform &field, byte *data, int32 offset) const;

		void setUniformStruct(const GLShaderUniform *uniform, byte *data, int32 offset) const;

		void setUniform1f(const string &name, float value) const;
		void setUniform1fv(const string &name, float *value, int32 count) const;
		void setUniform1i(const string &name, int32 value) const;
		void setUniform1iv(const string &name, int32 *value, int32 count) const;
		void setUniform2f(const string &name, const vec2 &vector) const;
		void setUniform3f(const string &name, const vec3 &vector) const;
		void setUniform4f(const string &name, const vec4 &vector) const;
		void setUniformMat4(const string &name, const mat4 &matrix) const;

		void setUniform1f(int32 location, float value) const;
		void setUniform1fv(int32 location, float *value, int32 count) const;
		void setUniform1i(int32 location, int32 value) const;
		void setUniform1iv(int32 location, int32 *value, int32 count) const;
		void setUniform2f(int32 location, const vec2 &vector) const;
		void setUniform3f(int32 location, const vec3 &vector) const;
		void setUniform4f(int32 location, const vec4 &vector) const;
		void setUniformMat4(int32 location, const mat4 &matrix) const;

	private:
		string name;
		uint handle;
		std::unordered_map<string, string> sources;

		ShaderUniformBufferVec uniformBuffers;
		ShaderSamplerVec samplers;
		ShaderStructVec structs;
	};

}}


#endif //X808_GLBASESHADER_HPP
