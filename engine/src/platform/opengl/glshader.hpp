//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLSHADER_HPP
#define X808_GLSHADER_HPP


#include "gfx/api/shader.hpp"
#include "glshaderuniform.hpp"
#include "glshaderresource.hpp"

namespace xe { namespace api {

	class GLShader : public Shader {
	public:
		explicit GLShader(const std::string_view &name, const std::vector<ShaderFile *> &shaderPipeline);
		~GLShader() override;

		void bind() const override;
		void unbind() const override;

		void setUniformBuffer(byte *data, uint size, uint slot) override;

		void setUniform(const std::string_view &name, byte *data) override;
		void resolveAndSetUniformField(const GLShaderUniform &field, byte *data, int32 offset);

	private:
		void resolveUniforms();
		uint getUniformLocation(const std::string_view &name);

		ShaderUniform *findUniform(const std::string_view &name, const ShaderUniformBuffer *buff);
		ShaderUniform *findUniform(const std::string_view &name);

		void resolveAndSetUniforms(ShaderUniformBuffer *buffer, byte *data, uint size);
		void resolveAndSetUniform(GLShaderUniform *uniform, byte *data, uint size);

		void setUniformStruct(const GLShaderUniform *uniform, byte *data, int32 offset);

		void setUniform1f(const std::string_view &name, float value);
		void setUniform1fv(const std::string_view &name, float *value, int32 count);
		void setUniform1i(const std::string_view &name, int32 value);
		void setUniform1iv(const std::string_view &name, int32 *value, int32 count);
		void setUniform2f(const std::string_view &name, const vec2 &vector);
		void setUniform3f(const std::string_view &name, const vec3 &vector);
		void setUniform4f(const std::string_view &name, const vec4 &vector);
		void setUniformMat4(const std::string_view &name, const mat4 &matrix);

		void setUniform1f(uint location, float value);
		void setUniform1fv(uint location, float *value, int32 count);
		void setUniform1i(uint location, int32 value);
		void setUniform1iv(uint location, int32 *value, int32 count);
		void setUniform2f(uint location, const vec2 &vector);
		void setUniform3f(uint location, const vec3 &vector);
		void setUniform4f(uint location, const vec4 &vector);
		void setUniformMat4(uint location, const mat4 &matrix);

	private:
		uint handle;
	};

}}


#endif //X808_GLSHADER_HPP
