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
#define SHADER_TID_INDEX           2
#define SHADER_COLOR_INDEX         3

#define SHADER_UNIFORM_PROJECTION_MATRIX_NAME    "sys_ProjectionMatrix"
#define SHADER_UNIFORM_VIEW_MATRIX_NAME          "sys_ViewMatrix"
#define SHADER_UNIFORM_MODEL_MATRIX_NAME         "sys_ModelMatrix"


	class XE_API Shader {
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setVSSystemUniformBuffer(byte *data, uint size, uint slot) = 0;
		virtual void setFSSystemUniformBuffer(byte *data, uint size, uint slot) = 0;

		virtual void setVSUserUniformBuffer(byte *data, uint size) = 0;
		virtual void setFSUserUniformBuffer(byte *data, uint size) = 0;

		virtual const std::string &getName() const = 0;
		virtual const std::string &getFile() const = 0;

		virtual const ShaderUniformBufferVec &getVSSystemUniforms() const = 0;
		virtual const ShaderUniformBufferVec &getFSSystemUniforms() const = 0;
		virtual const ShaderUniformBuffer *getVSUserUniformBuffer() const = 0;
		virtual const ShaderUniformBuffer *getFSUserUniformBuffer() const = 0;
		virtual const ShaderResourceVec &getResources() const = 0;

		static Shader *createFromFile(const std::string_view &name,
		                              const std::string_view &path,
		                              void *address = nullptr);

		static Shader *createFromSource(const std::string_view &name,
		                                const std::string &source,
		                                void *address = nullptr);

		static bool tryCompile(const std::string &source, std::string &error);
		static bool tryCompileFromFile(const std::string &file, std::string &error);
	};

}}}


#endif //X808_SHADER_HPP
