//
// Created by FLXR on 5/17/2019.
//

#ifndef X808_TEST0_HPP
#define X808_TEST0_HPP


#include "itestlayer.hpp"
#include "test01.hpp"
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>

class Test0 : public ITestLayer {
public:
  void init() override;

  void render() override;

  void input(xe::Event &event) override;

  ITEST_LAYER_METHODS(Test0)

protected:
  explicit Test0();
  ~Test0() override;

private:
  static Test0 *instance;

  xe::Camera *camera;
  xe::Renderer2D *renderer;

  xe::RectangleShape *shape;

  Test01 *other;
};


#endif //X808_TEST0_HPP
