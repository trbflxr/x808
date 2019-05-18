//
// Created by FLXR on 5/18/2019.
//

#ifndef X808_EXAMPLESHAPES2D_HPP
#define X808_EXAMPLESHAPES2D_HPP


#include "iexamplelayer.hpp"
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>
#include <xe/gfx/2d/circleshape.hpp>
#include <xe/gfx/2d/polygon.hpp>

class ExampleShapes2D : public IExampleLayer {
public:
  void init() override;

  void render() override;
  void renderImGui() override;

  void input(xe::Event &event) override;

  IEXAMPLE_LAYER_METHODS(ExampleShapes2D)

protected:
  explicit ExampleShapes2D();
  ~ExampleShapes2D() override;

private:
  void addPoint(const xe::vec2 &point);
  void createPolygon();
  void resetPolygon();

private:
  static constexpr float pointSize = 5.0f;
  static constexpr uint pointColor = xe::color::Cyan;

  static ExampleShapes2D *instance;

  xe::Camera *camera;
  xe::Renderer2D *renderer;

  xe::RectangleShape *rect;
  xe::CircleShape *circle;
  xe::Polygon *poly;

  std::vector<xe::IRenderable2D *> points;
  std::vector<xe::vec2> polyPoints;
  bool reset;
};


#endif //X808_EXAMPLESHAPES2D_HPP
