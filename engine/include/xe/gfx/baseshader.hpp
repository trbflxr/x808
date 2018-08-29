//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_BASESHADER_HPP
#define X808_BASESHADER_HPP


#include <cstring>
#include <string>
#include <unordered_map>
#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/resources/shaderfile.hpp>
#include <xe/gfx/shaderuniform.hpp>
#include <xe/gfx/shadersampler.hpp>

namespace xe {

	namespace internal {
		class PlatformBaseShader;
	}

	struct UniformData {
		byte *buffer;
		uint size;

		UniformData() = default;
		explicit UniformData(uint size) : size(size) {
			buffer = new byte[size];
			memset(buffer, 0, size);
		}
	};

	struct Uniform {
		const char *name;
		UniformData data;
		uint offset;

		Uniform() = default;
		explicit Uniform(const char *name, const UniformData &data, uint offset) :
				name(name), data(data), offset(offset) { }
	};

	class XE_API BaseShader {
	public:
		explicit BaseShader(const string &name, const std::vector<ShaderFile *> &shaderPipeline);
		~BaseShader();

		void bind() const;
		void unbind() const;

		void setUniformBuffer(byte *data, uint size, uint slot);

		const ShaderUniformBufferVec &getUniforms() const;
		const ShaderSamplerVec &getSamplers() const;
		const string &getName() const;
		const std::unordered_map<string, string> &getSources() const;

	private:
		internal::PlatformBaseShader *shader;
	};

}


#endif //X808_BASESHADER_HPP
