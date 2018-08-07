//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_SHADER_HPP
#define X808_SHADER_HPP


#include <cstring>
#include "common.hpp"
#include "xeint.hpp"
#include "math/math.hpp"
#include "resources/shaderfile.hpp"

namespace xe { namespace api {

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
		virtual ~Shader();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setUniformBuffer(byte *data, uint size, uint slot) = 0;
		virtual void setUniform(const std::string_view &name, byte *data) = 0;

		inline const ShaderUniformBufferVec &getUniforms() const { return uniformBuffers; }
		inline const ShaderResourceVec &getResources() const { return resources; }
		inline const std::string &getName() const { return name; };

		static Shader *create(const std::string_view &name,
		                      const std::vector<ShaderFile *> &shaderPipeline,
		                      void *address = nullptr);

	protected:
		explicit Shader(const std::string_view &name);

	protected:
		std::string name;
		uint version;

		ShaderUniformBufferVec uniformBuffers;
		ShaderResourceVec resources;
		ShaderStructVec structs;
	};

}}


#endif //X808_SHADER_HPP
