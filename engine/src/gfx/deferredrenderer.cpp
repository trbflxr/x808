//
// Created by FLXR on 3/5/2019.
//

#include <xe/gfx/deferredrenderer.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe {

  DeferredRenderer::DeferredRenderer(uint width, uint height, Camera *camera,
                                     ShadowParameters sp, fx::AOType aoType) :
      width(width),
      height(height),
      camera(camera),
      ambientLight(0.1f) {

    BufferLayout layout;
    layout.push<mat4>("view");
    layout.push<mat4>("projection");
    layout.push<vec4>("camPosition");
    layout.push<vec4>("camLook");

    cameraUBO = new UniformBuffer(BufferStorage::Dynamic, 1, layout);

    shadows = new Shadows(sp);
    gBuffer = new GBuffer(width, height, this);
    quad = new Quad(width, height);
    final = new fx::FinalFX(width, height);
    ao = new fx::AmbientOcclusion(width / 2, height / 2, aoType);
  }

  DeferredRenderer::~DeferredRenderer() {
    delete shadows;
    delete gBuffer;
    delete quad;
    delete final;
    delete cameraUBO;
    delete ao;
  }

  void DeferredRenderer::render(const Scene *scene) const {
    updateCamera();

    shadows->render(scene, camera);

    gBuffer->passDeferred(scene, shadows, quad);

    ao->calculateAO(gBuffer->getPositionTexture(),
                    gBuffer->getNormalTexture(),
                    gBuffer->getDepthStencilTexture(),
                    camera, quad);

    gBuffer->passLightAccumulation(ao->getAO(), ambientLight, quad, final->getFinalFBO());

    //render to screen
    final->render(quad);
  }

  void DeferredRenderer::updateCamera() const {
    const vec4 p = vec4(camera->getPosition(), 1.0f);
    const vec4 l = vec4(camera->getRotation().getForward(), 0.0f);

    cameraUBO->bind();
    cameraUBO->update(&camera->getView(), 0);
    cameraUBO->update(&camera->getProjection(), 1);
    cameraUBO->update(&p, 2);
    cameraUBO->update(&l, 3);
    cameraUBO->unbind();
  }

  void DeferredRenderer::renderModels(BeginMode mode, const Shader *shader,
                                      const std::vector<Model *> &models) const {

    for (const auto &m : models) {
      const mat4 &model = m->toMatrix();

      //world matrix
      shader->setUniform("model", &model, sizeof(mat4));

      const Material *mt = m->getMaterial();

      const vec3 &diffuseColor = mt->getDiffuseColor();
      const vec3 &specularColor = mt->getSpecularColor();
      const float emission = mt->getEmission();
      const float specularShininess = mt->getSpecularShininess();
      const float heightScale = mt->getHeightScale();

      //set mesh uniforms
      shader->setUniform("diffuseColor", &diffuseColor, sizeof(vec3));
      shader->setUniform("emissionStrength", &emission, sizeof(float));
      shader->setUniform("specularColor", &specularColor, sizeof(vec3));
      shader->setUniform("specularShininess", &specularShininess, sizeof(float));
      shader->setUniform("heightScale", &heightScale, sizeof(float));

      //textures
      uint df = setTexture(shader, mt->isUseDiffuse(), mt->getDiffuse(), "diffuseTexture", "enableDiffuseTexture");
      uint sp = setTexture(shader, mt->isUseSpecular(), mt->getSpecularMap(), "specularTexture", "enableSpecularTexture");
      uint nr = setTexture(shader, mt->isUseNormal(), mt->getNormalMap(), "normalTexture", "enableNormalTexture");
      uint ds = setTexture(shader, mt->isUseHeight(), mt->getHeightMap(), "heightTexture", "enableHeightTexture");

      shader->updateUniforms();
      m->render(mode);

      if (df) mt->getDiffuse()->unbind(df);
      if (sp) mt->getSpecularMap()->unbind(sp);
      if (nr) mt->getNormalMap()->unbind(nr);
      if (ds) mt->getHeightMap()->unbind(ds);
    }
  }

  void DeferredRenderer::renderLights(BeginMode mode, const Shader *shader,
                                      const std::vector<Light *> &lights) const {

    static constexpr int32 disabled = 0;

    for (const auto &light : lights) {
      if (!light->getMesh() || !light->isEnabled()) continue;

      //transform
      light->getBoundsMatrix();
      const mat4 &model = light->toMatrix();
      shader->setUniform("model", &model, sizeof(mat4));

      //values
      shader->setUniform("diffuseColor", &light->getColor(), sizeof(vec3));
      shader->setUniform("emissionStrength", &disabled, sizeof(float));

      //disable textures
      shader->setUniform("enableDiffuseTexture", &disabled, sizeof(int32));
      shader->setUniform("enableSpecularTexture", &disabled, sizeof(int32));
      shader->setUniform("enableNormalTexture", &disabled, sizeof(int32));
      shader->setUniform("enableHeightTexture", &disabled, sizeof(int32));

      shader->updateUniforms();

      //set cull face for light object
      if (light->getType() == LightType::Spot) {
        Renderer::setCullFace(CullFace::Back);
      } else {
        Renderer::setCullFace(CullFace::Front);
      }

      //render
      light->getMesh()->render(mode);

      //display bounds
      if (gBuffer->drawLightBoundsEnabled()) {
        Renderer::enableCullFace(false);
        Renderer::setPolygonMode(MaterialFace::FrontAndBack, PolygonMode::Line);

        renderLightBounds(shader, light);

        Renderer::setPolygonMode(MaterialFace::FrontAndBack, PolygonMode::Fill);
        Renderer::enableCullFace(true);
      }
    }

    Renderer::setCullFace(CullFace::Back);
  }

  void DeferredRenderer::renderLightBounds(const Shader *shader, const Light *light) const {
    shader->setUniform("model", &light->getBoundsMatrix(), sizeof(mat4));
    shader->updateUniforms();

    light->getMesh()->render(BeginMode::Triangles);
  }

  uint DeferredRenderer::setTexture(const Shader *shader, bool use, const Texture *texture,
                                    const char *sampler, const char *enable) const {

    static constexpr int32 enabled = 1;
    static constexpr int32 disabled = 0;

    if (!use || !texture) {
      shader->setUniform(enable, &disabled, sizeof(int32));
      return 0;
    }

    shader->setUniform(enable, &enabled, sizeof(int32));

    const uint slot = shader->getSampler(sampler);
    texture->bind(slot);

    return slot;
  }

}