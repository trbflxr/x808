//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_PLATFORMBASESHADER_HPP
#define X808_PLATFORMBASESHADER_HPP


#include <xe/xeint.hpp>
#include <xe/gfx/shadersampler.hpp>
#include <xe/gfx/shaderuniform.hpp>

namespace xe { namespace internal {

	class PlatformBaseShader {
	public:
		virtual ~PlatformBaseShader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setUniformBuffer(byte *data, uint size, uint slot) = 0;

		virtual const ShaderUniformBufferVec &getUniforms()  = 0;
		virtual const ShaderSamplerVec &getSamplers() const = 0;
		virtual const string &getName() const = 0;
	};

}}


#endif //X808_PLATFORMBASESHADER_HPP
