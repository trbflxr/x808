//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLSHADER_HPP
#define X808_GLSHADER_HPP


#include "gfx/api/shader.hpp"
#include "glshaderuniform.hpp"
#include "glshaderresource.hpp"

namespace xe { namespace gfx { namespace api {

	struct ShaderErrorInfo {
		uint shader;
		std::string message[2];
		uint line[2];
	};

	class GLShader : public Shader {
	private:
		friend class Shader;

	public:
		explicit GLShader(const std::string_view &name, const std::string &source);
		~GLShader();

		void bind() const override;
		void unbind() const override;

		void setVSSystemUniformBuffer(byte *data, uint size, uint slot) override;
		void setFSSystemUniformBuffer(byte *data, uint size, uint slot) override;

		void setVSUserUniformBuffer(byte *data, uint size) override;
		void setFSUserUniformBuffer(byte *data, uint size) override;

		void setUniform(const std::string_view &name, byte *data);
		void resolveAndSetUniformField(const GLShaderUniform &field, byte *data, int32 offset);

		inline const std::string &getName() const override { return name; }
		inline const std::string &getFile() const override { return file; }

		inline const ShaderUniformBufferVec &getVSSystemUniforms() const override { return vsUniformBuffers; }
		inline const ShaderUniformBufferVec &getFSSystemUniforms() const override { return fsUniformBuffers; }
		inline const ShaderUniformBuffer *getVSUserUniformBuffer() const override { return vsUserUniformBuffer; }
		inline const ShaderUniformBuffer *getFSUserUniformBuffer() const override { return fsUserUniformBuffer; }
		inline const ShaderResourceVec &getResources() const override { return resources; }

		static bool tryCompile(const std::string &source, std::string &error);
		static bool tryCompileFromFile(const std::string &file, std::string &error);

	private:
		static uint compile(std::string **shaders, ShaderErrorInfo *info);
		static void preProcess(const std::string &source, std::string **shaders);

		void parse(const std::string &vertexSource, const std::string &fragmentSource);
		void parseUniform(const std::string &statement, uint shaderType);
		void parseUniformStruct(const std::string &block, uint shaderType);

		bool isTypeStringResource(const std::string &type);

		ShaderStruct *findStruct(const std::string &name);

		void resolveUniforms();
		void validateUniforms();
		bool isSystemUniform(ShaderUniform *uniform) const;
		uint getUniformLocation(const std::string_view &name);

		ShaderUniform *findUniform(const std::string_view &name, const ShaderUniformBuffer *buff);
		ShaderUniform *findUniform(const std::string_view &name);

		void resolveAndSetUniforms(ShaderUniformBuffer *buffer, byte *data, uint size);
		void resolveAndSetUniform(GLShaderUniform *uniform, byte *data, uint size);

		void setUniformStruct(GLShaderUniform *uniform, byte *data, int32 offset);

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
		std::string name;
		std::string file;
		std::string source;
		std::string vertexSource;
		std::string fragmentSource;

		ShaderUniformBufferVec vsUniformBuffers;
		ShaderUniformBufferVec fsUniformBuffers;
		GLShaderUniformBuffer *vsUserUniformBuffer;
		GLShaderUniformBuffer *fsUserUniformBuffer;
		ShaderResourceVec resources;
		ShaderStructVec structs;
	};

}}}


#endif //X808_GLSHADER_HPP
