//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_PLATFORMBASESHADER_HPP
#define X808_PLATFORMBASESHADER_HPP


#include <unordered_map>
#include <xe/xeint.hpp>
#include <xe/gfx/shadersampler.hpp>
#include <xe/gfx/shaderuniform.hpp>
#include <xe/resources/shaderfile.hpp>

namespace xe::internal {

  class PlatformBaseShader {
  public:
    virtual ~PlatformBaseShader() = default;

    virtual void setSourceConstant(ShaderType type, const string &valueName, const string &value) = 0;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setUniformBuffer(byte *data, uint size, uint slot) const = 0;

    virtual void bindUniformBlock(const char *blockName, uint location) const = 0;

    virtual const ShaderUniformBufferVec &getUniforms() const = 0;
    virtual const ShaderSamplerVec &getSamplers() const = 0;
    virtual const ShaderConstantVec &getConstants(ShaderType type) const = 0;
    virtual const string &getName() const = 0;
    virtual uint getHandle() const = 0;
  };

}


#endif //X808_PLATFORMBASESHADER_HPP
