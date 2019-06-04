//
// Created by FLXR on 6/3/2019.
//

#ifndef X808_EXAMPLEPERFORMANCE2D_HPP
#define X808_EXAMPLEPERFORMANCE2D_HPP


#include "iexamplelayer.hpp"
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>

class ExamplePerformance2D : public IExampleLayer {
public:
  void render() override;

  void update(float delta) override;

  IEXAMPLE_LAYER_METHODS(ExamplePerformance2D)

protected:
  explicit ExamplePerformance2D();
  ~ExamplePerformance2D() override;

private:
  static ExamplePerformance2D *instance;

  xe::Camera *camera;
  xe::Renderer2D *renderer;

  uint sprites;
  std::vector<xe::IRenderable2D *> renderables;
  xe::Text *text;
};


#endif //X808_EXAMPLEPERFORMANCE2D_HPP
