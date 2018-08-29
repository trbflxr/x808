//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_SHADERSAMPLER_HPP
#define X808_SHADERSAMPLER_HPP


#include <vector>
#include <xe/utils/string.hpp>
#include <xe/xeint.hpp>

namespace xe {

	class ShaderSampler {
	public:
		enum class Type {
			None, Image2D, Image3D, Sampler1D, Sampler2D, Sampler2DArray, Sampler3D, SamplerCube, SamplerCubeArray
		};

	public:
		virtual ~ShaderSampler() = default;
		virtual const string &getName() const = 0;
		virtual uint getLocation() const = 0;
		virtual uint getCount() const = 0;
		virtual Type getType() const = 0;
	};
	typedef std::vector<ShaderSampler *> ShaderSamplerVec;

}


#endif //X808_SHADERSAMPLER_HPP
