//
// Created by FLXR on 5/27/2019.
//

#ifndef X808_EXAMPLEPARTICLES_HPP
#define X808_EXAMPLEPARTICLES_HPP


#include "iexamplelayer.hpp"
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/particles/particleeffect.hpp>

class ExampleParticles : public IExampleLayer {
public:
  void init() override;

  void render() override;
  void renderImGui() override;

  void update(float delta) override;
  void fixedUpdate(float delta) override;

  void input(xe::Event &event) override;

  IEXAMPLE_LAYER_METHODS(ExampleParticles)

protected:
  explicit ExampleParticles();
  ~ExampleParticles() override;

private:
  void drawRotationStates();
  void drawTranslationStates();
  void drawSizeStates();
  void drawColorStates();

private:
  static ExampleParticles *instance;

  xe::Camera *camera;
  xe::Renderer2D *renderer;

  bool renderBg;
  xe::RectangleShape *bg;

  xe::ParticleEffect *effect0;
  xe::ParticleEffect *effect1;

  std::vector<std::tuple<float, float, float>> rs;
  std::vector<std::tuple<float, xe::vec2, xe::vec2>> ts;
  std::vector<std::tuple<float, xe::vec2, xe::vec2>> ss;
  std::vector<std::tuple<float, xe::vec4, xe::vec4>> cs;

  bool updateRS;
  bool updateTS;
  bool updateSS;
  bool updateCS;
};


#endif //X808_EXAMPLEPARTICLES_HPP
