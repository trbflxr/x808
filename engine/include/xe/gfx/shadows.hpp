//
// Created by FLXR on 3/6/2019.
//

#ifndef X808_SHADOWS_HPP
#define X808_SHADOWS_HPP


#include <xe/config.hpp>
#include <xe/gfx/uniformbuffer.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/shader.hpp>

namespace xe {

  class Camera;
  class Scene;

  struct ShadowParameters {
    uint spotSize;
    uint maxSpotCount;
    uint dirSize;
    uint dirCascades;

    explicit ShadowParameters(const Config &config,
                              uint spotSize = 512,
                              uint dirSize = 1024) :
        spotSize(spotSize),
        maxSpotCount(config.maxSpotShadows),
        dirSize(dirSize),
        dirCascades(config.maxDirectionalCascades) { }
  };

  class XE_API Shadows : NonCopyable {
  public:
    explicit Shadows(ShadowParameters params);
    ~Shadows() override;

    void render(const Scene *scene, const Camera *camera);

    inline const Texture *getSpotShadows() const { return spotTexture; }
    inline const Texture *getDirShadows() const { return dirTexture; }

  private:
    void createTextures();
    void createBuffers();
    void createShaders();

    void renderSpotShadows(const Scene *scene);
    void renderDirectionalShadows(const Scene *scene, const Camera *camera);

    void renderScene(const Scene *scene, const Shader *shader, const FrameBuffer *buffer, uint count, uint size);

  private:
    ShadowParameters params;

    //spot shadows
    int32 spotShadowsIndex;
    FrameBuffer *spotBuffer;
    UniformBuffer *spotUBO;
    const Texture *spotDepthTexture;
    const Texture *spotTexture;
    const Shader *spotShader;

    //directional shadows
    FrameBuffer *dirBuffer;
    UniformBuffer *dirUBO;
    const Texture *dirDepthTexture;
    const Texture *dirTexture;
    const Shader *dirShader;
  };

}


#endif //X808_SHADOWS_HPP
