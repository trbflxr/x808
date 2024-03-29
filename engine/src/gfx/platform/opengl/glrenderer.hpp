//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLRENDERER_HPP
#define X808_GLRENDERER_HPP


#include <xe/gfx/renderer.hpp>
#include <gfx/platform/opengl/glcontext.hpp>

namespace xe::internal {

  class GLRenderer : public Renderer {
  public:
    explicit GLRenderer();

  protected:
    void initInternal() override;

    void clearBufferFInternal(Attachment buffer, const float color[4]) override;
    void clearInternal(uint buffer) override;
    void flushInternal() override;

    void setClearColorInternal(const vec4 &color) override;

    void enableVsyncInternal(bool enabled) override;
    void enableDepthTestingInternal(bool enabled) override;
    void enableBlendInternal(bool enabled) override;
    void enableDepthMaskInternal(bool enabled) override;
    void enableCullFaceInternal(bool enabled) override;
    void enableDepthClampInternal(bool enabled) override;
    void enableStencilTestInternal(bool enabled) override;

    void dispatchComputeInternal(uint numX, uint numY, uint numZ) override;

    void setViewportInternal(uint x, uint y, uint width, uint height) override;

    void setBlendFunctionInternal(BlendFunction source, BlendFunction destination) override;
    void setBlendEquationInternal(BlendEquation equation) override;
    void setDepthFunctionInternal(DepthFunction function) override;
    void setCullFaceInternal(CullFace cullFace) override;
    void setPolygonModeInternal(MaterialFace face, PolygonMode mode) override;
    void setStencilFuncInternal(StencilFunction func, uint ref, uint mask) override;
    void setStencilOpSeparateInternal(StencilFace face, StencilOp sf, StencilOp dpf, StencilOp dpp) override;
    void setMemoryBarrierInternal(MemoryBarrier barrier) override;

  private:
    GLContext *context;
  };

}


#endif //X808_GLRENDERER_HPP
