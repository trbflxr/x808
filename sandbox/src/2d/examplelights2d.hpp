//
// Created by FLXR on 5/18/2019.
//

#ifndef X808_EXAMPLELIGHTS2D_HPP
#define X808_EXAMPLELIGHTS2D_HPP


#include "iexamplelayer.hpp"
#include "2d/cameramovement2d.hpp"
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>

class ExampleLights2D : public IExampleLayer {
public:
  void init() override;

  void render() override;
  void renderImGui() override;

  void update(float delta) override;

  void input(xe::Event &event) override;

  IEXAMPLE_LAYER_METHODS(ExampleLights2D)

protected:
  explicit ExampleLights2D();
  ~ExampleLights2D() override;

private:
  void spawnLight();

private:
  static ExampleLights2D *instance;

  CameraMovement2D *cm;
  xe::Camera *camera;
  xe::Renderer2D *renderer;

  xe::RectangleShape *bg;
  xe::RectangleShape *pepe;
  xe::RectangleShape *rock;
  xe::RectangleShape *sand;
  std::vector<xe::Light2D *> lights;

  static constexpr int32 maxLights = 50;

  int32 lightsToRender;
  int32 lightsCount;
  xe::vec3 ambientColor;
  xe::vec3 color;
  float intensity;
};


#endif //X808_EXAMPLELIGHTS2D_HPP
