//
// Created by FLXR on 5/17/2019.
//

#include "test0.hpp"
#include <xe/resources/texturemanager.hpp>

using namespace xe;

Test0 *Test0::instance = nullptr;

Test0::Test0() {
  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1000.0f));
  renderer = new Renderer2D(width, height, camera);

  shape = new RectangleShape({width, height});
}

Test0::~Test0() {
  delete camera;
  delete renderer;
  delete shape;
}

void Test0::init() {
  shape->setTexture(GETTEXTURE("grass.png"));
//  shape->setPosition()
}

void Test0::render() {
  renderer->begin();

  renderer->submit(shape);

  renderer->end();
  renderer->flush();
}

void Test0::input(xe::Event &event) {

}
