//
// Created by FLXR on 5/18/2019.
//

#include "examplelights2d.hpp"
#include <xe/resources/texturemanager.hpp>
#include <xe/ui/imgui/imgui.h>

using namespace xe;

ExampleLights2D *ExampleLights2D::instance = nullptr;

ExampleLights2D::ExampleLights2D() :
    lightsToRender(1),
    lightsCount(0),
    ambientColor(0.4f),
    color(1.0f),
    intensity(100.0f) {

  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f));
  renderer = new Renderer2D(width, height, camera, maxLights);
  renderer->setAmbientLight(ambientColor);

  cm = new CameraMovement2D(camera, 1000.0f);

  bg = new RectangleShape({1920 * 2.0f, 1080 * 2.0f});
  pepe = new RectangleShape({200.0f, 200.0f});
  rock = new RectangleShape({400.0f, 400.0f});
  sand = new RectangleShape({400.0f, 400.0f});
}

ExampleLights2D::~ExampleLights2D() {
  delete cm;
  delete camera;
  delete renderer;
  delete bg;
  delete pepe;
  delete rock;
  delete sand;

  for (auto &&l : lights) {
    delete l;
  }
  lights.clear();
}

void ExampleLights2D::init() {
  bg->setTexture(GETTEXTURE("bg"));
  bg->move(app.getWindowSize() / 2.0f);

  pepe->setTexture(GETTEXTURE("pepe"));
  pepe->move({400.0f, 200.0f});

  rock->setTexture(GETTEXTURE("rock_d"));
  rock->move({800.0f, 200.0f});

  sand->setTexture(GETTEXTURE("ground_d"));
  sand->move({1300.0f, 200.0f});

  const vec2 spawnPos = Mouse::getPosition(app.getWindow()) / 2.0f;
  Light2D *l = new Light2D("light", spawnPos, {1.0f, 0.0f, 1.0f}, 200.0f);
  lights.push_back(l);
  ++lightsCount;
}

void ExampleLights2D::render() {
  int32 used = 0;
  for (auto &&l : lights) {
    renderer->useLight(l);
    if (++used >= lightsToRender) break;
  }

  renderer->begin();

  renderer->submit(bg);
  renderer->submit(pepe);
  renderer->submit(rock);
  renderer->submit(sand);

  renderer->end();
  renderer->flush();
}

void ExampleLights2D::renderImGui() {
  ImGui::Begin("Lights 2D", nullptr);

  if (ImGui::ColorEdit3("Ambient color", reinterpret_cast<float *>(&ambientColor))) {
    renderer->setAmbientLight(ambientColor);
  }
  ImGui::Separator();
  ImGui::Text("WASD - move");
  ImGui::Text("LMB - spawn light");
  ImGui::Separator();

  ImGui::Text("Lights count: %i", lightsCount);

  if (ImGui::DragInt("Max lights", &lightsToRender, 0.1f, 1, maxLights)) {
    renderer->setMaxLights(lightsToRender);
  }

  ImGui::ColorEdit3("Color", reinterpret_cast<float *>(&color));
  ImGui::DragFloat("Intensity", &intensity, 0.1f, 0.02f, 200.0f);

  ImGui::End();
}

void ExampleLights2D::update(float delta) {
  cm->update(delta);
}

void ExampleLights2D::input(xe::Event &event) {
  if (event.type == Event::MouseButtonPressed) {
    if (event.mouseButton.button == Mouse::Left) {
      spawnLight();
    }
  }
}

void ExampleLights2D::spawnLight() {
  if (lightsCount >= maxLights || lightsToRender <= lightsCount) return;

  ++lightsCount;

  const vec2 spawnPos = vec2(camera->getPosition()) + Mouse::getPosition(app.getWindow());

  Light2D *l = new Light2D("light", spawnPos, color, intensity);
  lights.push_back(l);
}
