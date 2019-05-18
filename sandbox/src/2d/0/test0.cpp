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

  camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f));
  renderer = new Renderer2D(width, height, camera);

  shape = new RectangleShape({500.0f, 500.0f});

  other = Test01::create();
}

Test0::~Test0() {
  delete camera;
  delete renderer;
  delete shape;

  app.popLayer();
  Test01::destroy();
}

void Test0::init() {
  app.pushLayer(other);
  other->init();

  shape->setTexture(GETTEXTURE("grass"));
  shape->move(app.getWindowSize() / 2.0f);
}

void Test0::render() {
  renderer->begin();

  renderer->submit(shape);

  renderer->end();
  renderer->flush();
}

void Test0::input(xe::Event &event) {
  if (event.type == Event::MouseButtonPressed) {
    if (event.mouseButton.button == Mouse::Left) {
      if (shape->contains(vec2(event.mouseButton.x, event.mouseButton.y))) {
        XE_INFO("Hello from layer 0");
      }
    }
  }
}
