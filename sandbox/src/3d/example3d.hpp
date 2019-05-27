//
// Created by FLXR on 5/19/2019.
//

#ifndef X808_EXAMPLE3D_HPP
#define X808_EXAMPLE3D_HPP


#include "iexamplelayer.hpp"
#include "dummyplayer.hpp"
#include "examplescene.hpp"
#include <xe/gfx/deferredrenderer.hpp>

class Example3D : public IExampleLayer {
public:
  void init() override;

  void render() override;
  void renderImGui() override;

  void update(float delta) override;
  void fixedUpdate(float delta) override;

  void input(xe::Event &event) override;

  IEXAMPLE_LAYER_METHODS(Example3D)

protected:
  explicit Example3D();
  ~Example3D() override;

private:
  void drawLightsConfig();
  void drawAmbientTab();
  void drawDirectionalTab();
  void drawSpotTab();
  void drawPointTab();


private:
  static Example3D *instance;

  DummyPlayer *player;
  xe::Camera *camera;

  ExampleScene *scene;
  xe::DeferredRenderer *renderer;

  bool lightsConfig;
  bool dlHooked;
  bool slHooked;
  bool plHooked;
};


#endif //X808_EXAMPLE3D_HPP
