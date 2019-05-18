//
// Created by FLXR on 5/18/2019.
//

#include "test01.hpp"
#include <xe/resources/texturemanager.hpp>
#include <xe/ui/imgui/imgui.h>

using namespace xe;

Test01 *Test01::instance = nullptr;

Test01::Test01() :
    block(false) {

  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f));
  renderer = new Renderer2D(width, height, camera);

  shape = new RectangleShape({250.0f, 250.0f});
}

Test01::~Test01() {
  delete camera;
  delete renderer;
  delete shape;
}

void Test01::init() {
  shape->setTexture(GETTEXTURE("rock"));
  shape->move(app.getWindowSize() / 2.0f);
}

void Test01::render() {
  renderer->begin();

  renderer->submit(shape);

  renderer->end();
  renderer->flush();
}

void Test01::renderImGui() {
  ImGui::Begin("Test0_1", nullptr);

  if (ImGui::Button("Toggle block")) {
    block = !block;
  }
  ImGui::Text("Event blocked: %s", block ? "true" : "false");

  ImGui::End();
}

void Test01::update(float delta) {
  if (shape->contains(Mouse::getPosition(app.getWindow()))) {
    shape->setColor(color::Red);
  } else {
    shape->setColor(color::White);
  }
}

void Test01::input(xe::Event &event) {
  if (event.type == Event::MouseButtonPressed) {
    if (event.mouseButton.button == Mouse::Left) {
      if (shape->contains({event.mouseButton.x, event.mouseButton.y})) {
        XE_INFO("Hello from layer 1");
        event.handled = block;
      }
    }
  }
}

