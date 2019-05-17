//
// Created by FLXR on 5/17/2019.
//

#ifndef X808_MAINMENU_HPP
#define X808_MAINMENU_HPP


#include "itestlayer.hpp"
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>

class MainMenu : public xe::Layer {
public:
  explicit MainMenu();
  ~MainMenu() override;

  void render() override;
  void renderImGui() override;

  void update(float delta) override;
  void fixedUpdate(float delta) override;

  void input(xe::Event &event) override;

protected:
  void resize(int32 width, int32 height) override;

private:
  void showTest(ITestLayer *layer);
  void popTest();

private:
  ITestLayer *current;

  xe::Camera *camera;
  xe::Renderer2D *renderer;
  xe::RectangleShape *bg;
};


#endif //X808_MAINMENU_HPP
