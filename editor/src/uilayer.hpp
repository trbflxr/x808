//
// Created by FLXR on 9/7/2018.
//

#ifndef X808_UILAYER_HPP
#define X808_UILAYER_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/quad.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/2d/renderer2d.hpp>

namespace xe {

  class UILayer : public Layer {
  public:
    explicit UILayer();
    ~UILayer() override;

    void render() override;
    void renderImGui() override;

    void update(float delta) override;
    void fixedUpdate(float delta) override;

    void input(Event &event) override;

  private:
    //framebuffer
    FrameBuffer *renderWindow;
    Texture *renderTexture;
    Quad *quad;

    //test
    Camera *camera;
    Renderer2D *renderer;

    std::vector<IRenderable2D *> renderables;
  };

}


#endif //X808_UILAYER_HPP
