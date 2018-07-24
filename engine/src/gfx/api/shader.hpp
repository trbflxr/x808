//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_SHADER_HPP
#define X808_SHADER_HPP


#include <cstring>
#include "common.hpp"
#include "xeint.hpp"
#include "shaderuniform.hpp"
#include "shaderresource.hpp"
#include "math/math.hpp"

namespace xe { namespace gfx { namespace api {

	struct UniformBuffer {
		byte *buffer;
		uint size;

		UniformBuffer() = default;
		explicit UniformBuffer(byte *buffer, uint size) :
				buffer(buffer), size(size) {
			memset(buffer, 0, size);
		}
	};

	struct Uniform {
		const char *name;
		UniformBuffer buffer;
		uint offset;

		Uniform() = default;
		explicit Uniform(const char *name, const UniformBuffer &buffer, uint offset) :
				name(name), buffer(buffer), offset(offset) { }
	};

	class XE_API Shader {
	public:
		enum {
			UNDEFINED = 0, VERT, FRAG
		};

	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setVSSystemUniformBuffer(byte *data, uint size, uint slot) = 0;
		virtual void setFSSystemUniformBuffer(byte *data, uint size, uint slot) = 0;

		virtual void setVSUserUniformBuffer(byte *data, uint size) = 0;
		virtual void setFSUserUniformBuffer(byte *data, uint size) = 0;

		virtual const std::string &getName() const = 0;
		virtual const std::string &getFile() const = 0;

		virtual void setUniform(const std::string_view &name, byte *data) = 0;

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
