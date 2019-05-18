//
// Created by FLXR on 5/18/2019.
//

#ifndef X808_TEST01_HPP
#define X808_TEST01_HPP


#include "itestlayer.hpp"
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>

class Test01 : public ITestLayer {
public:
  void init() override;

  void render() override;
  void renderImGui() override;

  void update(float delta) override;

  void input(xe::Event &event) override;

  ITEST_LAYER_METHODS(Test01)

protected:
  explicit Test01();
  ~Test01() override;

private:
  static Test01 *instance;

  xe::Camera *camera;
  xe::Renderer2D *renderer;

  xe::RectangleShape *shape;

  bool block;
};


#endif //X808_TEST01_HPP
