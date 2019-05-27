//
// Created by FLXR on 5/17/2019.
//

#include "example0.hpp"
#include <xe/resources/texturemanager.hpp>

using namespace xe;

Example0 *Example0::instance = nullptr;

Example0::Example0() {
  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f));
  renderer = new Renderer2D(width, height, camera);

  shape = new RectangleShape({500.0f, 500.0f});

  other = Example01::create();
}

Example0::~Example0() {
  delete camera;
  delete renderer;
  delete shape;

  app.popLayer();
  Example01::destroy();
}

void Example0::init() {
  app.pushLayer(other);
  other->init();

  shape->setTexture(GETTEXTURE("grass"));
  shape->move(app.getWindowSize() / 2.0f);
}

void Example0::render() {
  renderer->begin();

  renderer->submit(shape);

  renderer->end();
  renderer->flush();
}

void Example0::input(xe::Event &event) {
  if (event.type == Event::MouseButtonPressed) {
    if (event.mouseButton.button == Mouse::Left) {
      if (shape->contains(vec2(event.mouseButton.x, event.mouseButton.y))) {
        XE_INFO("Hello from layer 0");
      }
    }
  }
}
