//
// Created by FLXR on 2/8/2019.
//

#ifndef X808_TESTL2D_HPP
#define X808_TESTL2D_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>
#include <xe/animation/spriteanimation.hpp>
#include <xe/audio/audiosource.hpp>

class TestL2D : public xe::Layer {
public:
  explicit TestL2D();
  ~TestL2D() override;

  void render() override;
  void renderImGui() override;

  void update(float delta) override;
  void fixedUpdate(float delta) override;

  void input(xe::Event &event) override;

protected:
  void resize(int32 width, int32 height) override;

private:
  xe::Camera *camera;
  xe::Renderer2D *renderer;

  xe::RectangleShape *box0;
  xe::RectangleShape *box1;

  xe::SpriteAnimation *playerAnimation;
  xe::RectangleShape *player;

  std::vector<xe::Light2D *> lights;
  std::vector<xe::IRenderable2D *> renderables;

  xe::AudioSource *as0;
};


#endif //X808_TESTL2D_HPP
