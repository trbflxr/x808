//
// Created by FLXR on 5/18/2019.
//

#ifndef X808_EXAMPLETEXT_HPP
#define X808_EXAMPLETEXT_HPP


#include "iexamplelayer.hpp"
#include <xe/gfx/2d/renderer2d.hpp>

class ExampleText : public IExampleLayer {
public:
  void init() override;

  void render() override;
  void renderImGui() override;

  void input(xe::Event &event) override;

  IEXAMPLE_LAYER_METHODS(ExampleText)

protected:
  explicit ExampleText();
  ~ExampleText() override;

private:
  static ExampleText *instance;

  xe::Camera *camera;
  xe::Renderer2D *renderer;

  xe::Text *text;
  xe::Text *text0;
  xe::Text *text1;
  xe::Text *text2;
  xe::Text *text3;
  xe::Text *text4;

  float scale;
  xe::vec3 textColor;
  xe::vec3 outlineColor;
  xe::string inputString;
};


#endif //X808_EXAMPLETEXT_HPP
