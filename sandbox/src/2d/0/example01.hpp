//
// Created by FLXR on 5/18/2019.
//

#ifndef X808_EXAMPLE01_HPP
#define X808_EXAMPLE01_HPP


#include "iexamplelayer.hpp"
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>

class Example01 : public IExampleLayer {
public:
  void init() override;

  void render() override;
  void renderImGui() override;

  void update(float delta) override;

  void input(xe::Event &event) override;

  IEXAMPLE_LAYER_METHODS(Example01)

protected:
  explicit Example01();
  ~Example01() override;

private:
  static Example01 *instance;

  xe::Camera *camera;
  xe::Renderer2D *renderer;

  xe::RectangleShape *shape;

  bool block;
};


#endif //X808_EXAMPLE01_HPP
