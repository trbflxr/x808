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

		void setUniformBuffer(byte *data, uint size, uint slot) override;

		inline const ShaderUniformBufferVec &getUniforms() override { return uniformBuffers; }
		inline const ShaderSamplerVec &getSamplers() const override { return samplers; }
		inline const string &getName() const override { return name; }
		inline const std::unordered_map<string, string> &getSources() const override { return sources; }

	private:
		void resolveUniforms();
		uint getUniformLocation(const string &name, bool runTime = true);

		ShaderUniform *findUniform(const string &name, const ShaderUniformBuffer *buff);
		ShaderUniform *findUniform(const string &name);

		void resolveAndSetUniforms(ShaderUniformBuffer *buffer, byte *data, uint size);
		void resolveAndSetUniform(GLShaderUniform *uniform, byte *data, uint size);

		void resolveAndSetUniformField(const GLShaderUniform &field, byte *data, int32 offset);

		void setUniformStruct(const GLShaderUniform *uniform, byte *data, int32 offset);

		void setUniform1f(const string &name, float value);
		void setUniform1fv(const string &name, float *value, int32 count);
		void setUniform1i(const string &name, int32 value);
		void setUniform1iv(const string &name, int32 *value, int32 count);
		void setUniform2f(const string &name, const vec2 &vector);
		void setUniform3f(const string &name, const vec3 &vector);
		void setUniform4f(const string &name, const vec4 &vector);
		void setUniformMat4(const string &name, const mat4 &matrix);

		void setUniform1f(uint location, float value);
		void setUniform1fv(uint location, float *value, int32 count);
		void setUniform1i(uint location, int32 value);
		void setUniform1iv(uint location, int32 *value, int32 count);
		void setUniform2f(uint location, const vec2 &vector);
		void setUniform3f(uint location, const vec3 &vector);
		void setUniform4f(uint location, const vec4 &vector);
		void setUniformMat4(uint location, const mat4 &matrix);

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
