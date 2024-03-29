//
// Created by FLXR on 3/2/2019.
//

#ifndef X808_GBUFFER_HPP
#define X808_GBUFFER_HPP


#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/model.hpp>
#include <xe/gfx/light.hpp>
#include <xe/gfx/quad.hpp>
#include <xe/gfx/scene.hpp>
#include <xe/gfx/shadows.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

  class DeferredRenderer;

  class XE_API GBuffer : NonCopyable {
  public:
    explicit GBuffer(uint width, uint height, DeferredRenderer *renderer);
    ~GBuffer() override;

    void passDeferred(const Scene *scene, const Shadows *shadows, const Quad *quad) const;
    void passLightAccumulation(const Texture *aoTexture, const vec3 &ambient,
                               const Quad *quad, const FrameBuffer *final) const;

    void setShadowQuality(uint value);
    void setMaxParallaxLayers(uint value);

    inline uint getWidth() const { return width; }
    inline uint getHeight() const { return height; }

    inline const Texture *getDepthStencilTexture() const { return depthStencilTexture; }
    inline const Texture *getDiffuseTexture() const { return diffuseTexture; }
    inline const Texture *getNormalTexture() const { return normalTexture; }
    inline const Texture *getSpecularTexture() const { return specularTexture; }
    inline const Texture *getPositionTexture() const { return positionTexture; }
    inline const Texture *getLightDiffuseTexture() const { return lightDiffuseTexture; }
    inline const Texture *getLightSpecularTexture() const { return lightSpecularTexture; }

    inline void enableCullTest(bool enabled) { cullTest = enabled; }
    inline void enableWireframe(bool enabled) { drawWireframe = enabled; }
    inline void enableLightObjects(bool enabled) { drawLightObjects = enabled; }
    inline void enableLightBounds(bool enabled) { drawLightBounds = enabled; }

    inline bool cullTestEnabled() const { return cullTest; }
    inline bool drawWireframeEnabled() const { return drawWireframe; }
    inline bool drawLightObjectsEnabled() const { return drawLightObjects; }
    inline bool drawLightBoundsEnabled() const { return drawLightBounds; }

  private:
    void createTextures();
    void createShaders();

    void passGeometryInternal(const Scene *scene) const;
    void passStencil(const Light *light) const;
    void passSpotLight(const SpotLight *light, const Shadows *shadows) const;
    void passPointLight(const PointLight *light) const;
    void passDirectionalLight(const DirectionalLight *light, const Shadows *shadows, const Quad *quad) const;

  private:
    uint width;
    uint height;
    vec2 renderSize;

    DeferredRenderer *renderer;

    bool cullTest;
    bool drawWireframe;
    bool drawLightObjects;
    bool drawLightBounds;

    FrameBuffer *gBuffer;

    const Shader *geometryShader;
    const Shader *stencilShader;
    const Shader *accumulationShader;
    const Shader *spotShader;
    const Shader *pointShader;
    const Shader *directionalShader;

    const Texture *depthStencilTexture;
    const Texture *diffuseTexture;
    const Texture *normalTexture;
    const Texture *specularTexture;
    const Texture *positionTexture;
    const Texture *lightDiffuseTexture;
    const Texture *lightSpecularTexture;
  };

}

#endif //X808_GBUFFER_HPP
