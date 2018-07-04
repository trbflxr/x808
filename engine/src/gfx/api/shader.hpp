//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_SHADER_HPP
#define X808_SHADER_HPP


#include "common.hpp"
#include "xeint.hpp"
#include "shaderuniform.hpp"
#include "shaderresource.hpp"
#include "math/math.hpp"

namespace xe { namespace gfx { namespace api {

#define SHADER_VERTEX_INDEX        0
#define SHADER_UV_INDEX            1
#define SHADER_TID_INDEX        2
#define SHADER_COLOR_INDEX        3

#define SHADER_UNIFORM_PROJECTION_MATRIX_NAME    "sys_ProjectionMatrix"
#define SHADER_UNIFORM_VIEW_MATRIX_NAME          "sys_ViewMatrix"
#define SHADER_UNIFORM_MODEL_MATRIX_NAME         "sys_ModelMatrix"

	struct ShaderErrorInfo {
		uint shader;
		std::string message[2];
		uint line[2];
	};

	class XE_API Shader  {
	public:
		explicit Shader(const std::string_view &name, const std::string &source);
		~Shader();

		void bind() const;
		void unbind() const;

		void setVSSystemUniformBuffer(byte *data, uint size, uint slot);
		void setFSSystemUniformBuffer(byte *data, uint size, uint slot);

		void setVSUserUniformBuffer(byte *data, uint size);
		void setFSUserUniformBuffer(byte *data, uint size);

		void setUniform(const std::string_view &name, byte *data);
		void resolveAndSetUniformField(const ShaderUniform &field, byte *data, int32 offset);

		inline const std::string &getName() const { return name; }
		inline const std::string &getFile() const { return file; }

		inline const ShaderUniformBufferVec &getVSSystemUniforms() const { return vsUniformBuffers; }
		inline const ShaderUniformBufferVec &getFSSystemUniforms() const { return fsUniformBuffers; }
		inline const ShaderUniformBuffer *getVSUserUniformBuffer() const { return vsUserUniformBuffer; }
		inline const ShaderUniformBuffer *getFSUserUniformBuffer() const { return fsUserUniformBuffer; }
		inline const ShaderResourceVec &getResources() const { return resources; }

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
		void resolveAndSetUniform(ShaderUniform *uniform, byte *data, uint size);

		void setUniformStruct(ShaderUniform *uniform, byte *data, int32 offset);

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
		ShaderUniformBuffer *vsUserUniformBuffer;
		ShaderUniformBuffer *fsUserUniformBuffer;
		ShaderResourceVec resources;
		ShaderStructVec structs;
	};

}}}


#endif //X808_SHADER_HPP
