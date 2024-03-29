//
// Created by FLXR on 5/18/2019.
//

#include "example01.hpp"
#include <xe/resources/texturemanager.hpp>
#include <xe/ui/imgui/imgui.h>
#include <xe/gfx/renderer.hpp>

using namespace xe;

Example01 *Example01::instance = nullptr;

Example01::Example01() :
    clearColor(color::decode(0x946EC6)),
    block(false) {

  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f));
  renderer = new Renderer2D(width, height, camera);

  shape = new RectangleShape({250.0f, 250.0f});
}

Example01::~Example01() {
  delete camera;
  delete renderer;
  delete shape;
}

void Example01::init() {
  shape->setTexture(GETTEXTURE("pepe"));
  shape->move(app.getWindowSize() / 2.0f);

  Renderer::setClearColor(color::encode(vec4(clearColor, 1.0f)));
}

void Example01::render() {
  renderer->begin();

  renderer->submit(shape);

  renderer->end();
  renderer->flush();
}

void Example01::renderImGui() {
  ImGui::Begin("Basics", nullptr);

  if (ImGui::ColorPicker3("Clear color", reinterpret_cast<float *>(&clearColor))) {
    Renderer::setClearColor(color::encode(vec4(clearColor, 1.0f)));
  }

  ImGui::Separator();
  if (ImGui::Button("Toggle event block")) {
    block = !block;
  }
  ImGui::Text("Event blocked: %s", block ? "true" : "false");

  ImGui::End();
}

void Example01::update(float delta) {
  if (shape->contains(Mouse::getPosition(app.getWindow()))) {
    shape->setColor(color::Red);
  } else {
    shape->setColor(color::White);
  }
}

void Example01::input(xe::Event &event) {
  if (event.type == Event::MouseButtonPressed) {
    if (event.mouseButton.button == Mouse::Left) {
      if (shape->contains({event.mouseButton.x, event.mouseButton.y})) {
        XE_INFO("Hello from layer 1");
        event.handled = block;
      }
    }
  }
}
