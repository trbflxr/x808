//
// Created by FLXR on 3/21/2019.
//

#ifndef X808_EMPTYSCENE_HPP
#define X808_EMPTYSCENE_HPP

#include <xe/gfx/layer.hpp>
#include <xe/gfx/2d/renderer2d.hpp>

class EmptyScene : public xe::Layer {
public:
  explicit EmptyScene();
  ~EmptyScene() override;

  void render() override;
  void renderImGui() override;

  void update(float delta) override;
  void fixedUpdate(float delta) override;

  void input(xe::Event &event) override;
};

#endif //X808_EMPTYSCENE_HPP
