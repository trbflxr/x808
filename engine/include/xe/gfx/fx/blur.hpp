//
// Created by FLXR on 3/20/2019.
//

#ifndef X808_BLUR_HPP
#define X808_BLUR_HPP


#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/quad.hpp>
#include <xe/gfx/fx/rendereffect.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe { namespace fx {

  class XE_API Blur : public RenderEffect, NonCopyable {
  public:
    explicit Blur(uint width, uint height);
    ~Blur() override;

    void blur(const Texture *texture, const Quad *quad);

    inline const Texture *getTexture() const { return blurTextureHor; }

  private:
    uint sampler0;

    FrameBuffer *blurBuffer;
    Texture *blurTextureVert;
    Texture *blurTextureHor;
    const Shader *blurShader;
  };

}}


#endif //X808_BLUR_HPP
