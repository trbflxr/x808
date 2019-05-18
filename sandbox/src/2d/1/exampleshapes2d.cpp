//
// Created by FLXR on 5/18/2019.
//

#include "exampleshapes2d.hpp"
#include <xe/resources/texturemanager.hpp>
#include <xe/ui/imgui/imgui.h>
#include <xe/gfx/renderer.hpp>

using namespace xe;

ExampleShapes2D *ExampleShapes2D::instance = nullptr;

ExampleShapes2D::ExampleShapes2D() :
    reset(false) {

  const float width = app.getWindowSize().x;
  const float height = app.getWindowSize().y;

  camera = new Camera(mat4::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f));
  renderer = new Renderer2D(width, height, camera);

  circle = new CircleShape(50.0f);
  rect = new RectangleShape({200.0f, 200.0f});
  poly = new Polygon();
}

ExampleShapes2D::~ExampleShapes2D() {
  delete camera;
  delete renderer;
  delete rect;
  delete circle;
  delete poly;

  for (auto &&p : points) {
    delete p;
  }
}

void ExampleShapes2D::init() {
  rect->setTexture(GETTEXTURE("pepe"));
  rect->move(app.getWindowSize() / 2.0f);

  circle->setTexture(GETTEXTURE("grass"));
  circle->move({400.0f, 200.0f});

  poly->setTexture(GETTEXTURE("sp0"));

  Renderer::setClearColor(0x468B81);
}

void ExampleShapes2D::render() {
  renderer->begin();

  renderer->submit(rect);
  renderer->submit(circle);
  renderer->submit(poly);

  for (auto &&p : points) {
    renderer->submit(p);
  }

  renderer->end();
  renderer->flush();
}

void ExampleShapes2D::renderImGui() {
  ImGui::Begin("Shapes 2D", nullptr);

  if (ImGui::Button("Create polygon (C)")) {
    createPolygon();
  }
  if (ImGui::Button("Reset polygon (R)")) {
    resetPolygon();
  }

  ImGui::End();
}

void ExampleShapes2D::input(Event &event) {
  if (event.type == Event::MouseButtonPressed) {
    if (event.mouseButton.button == Mouse::Left) {
      addPoint({event.mouseButton.x, event.mouseButton.y});
    }
  }

  if (event.type == Event::KeyPressed) {
    if (event.key.code == Keyboard::C) {
      createPolygon();
    }
    if (event.key.code == Keyboard::R) {
      resetPolygon();
    }
  }
}

void ExampleShapes2D::addPoint(const vec2 &point) {
  if (reset) {
    resetPolygon();
  }

  polyPoints.push_back(point);

  CircleShape *c = new CircleShape(pointSize);
  c->setColor(pointColor);
  c->transformation(point);
  points.push_back(c);
}

void ExampleShapes2D::createPolygon() {
  if (polyPoints.size() < 3) return;

  reset = true;

  poly->reshape(polyPoints);
  poly->setVisible(true);
}

void ExampleShapes2D::resetPolygon() {
  poly->setVisible(false);

  for (auto &&p : points) {
    delete p;
  }
  points.clear();
  polyPoints.clear();

  reset = false;
}
