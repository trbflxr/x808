//
// Created by FLXR on 5/17/2019.
//

#ifndef X808_EXAMPLE0_HPP
#define X808_EXAMPLE0_HPP


#include "iexamplelayer.hpp"
#include "example01.hpp"
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>

class Example0 : public IExampleLayer {
public:
  void init() override;

  void render() override;

  void input(xe::Event &event) override;

  IEXAMPLE_LAYER_METHODS(Example0)

protected:
  explicit Example0();
  ~Example0() override;

private:
  static Example0 *instance;

  xe::Camera *camera;
  xe::Renderer2D *renderer;

  xe::RectangleShape *shape;

  Example01 *other;
};


#endif //X808_EXAMPLE0_HPP
