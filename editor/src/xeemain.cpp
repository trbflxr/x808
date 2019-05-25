//
// Created by FLXR on 9/7/2018.
//

#include <xe/app/application.hpp>
#include <xe/core/vfs.hpp>
#include "uilayer.hpp"

class Editor : public xe::Application {
public:
  explicit Editor(const xe::Config &config) :
      Application(config, "XE Editor") {

    xe::VFS::mount("fonts", "xe_sandbox_assets/fonts/");
    xe::VFS::mount("textures", "xe_sandbox_assets/textures/");

    xe::UILayer *ui = new xe::UILayer();

    pushLayer(ui);
  }

  ~Editor() override { }
};

int main() {
  xe::initialize();

  xe::Config config;
  config.width = 1280;
  config.height = 720;
  config.fullScreen = 0;
  config.vSync = false;
  config.maxFps = 0;
  config.tickRate = 30;
  config.srgb = true;
  config.renderApi = xe::RenderAPI::OpenGL;
  config.apiVersion = 330;

  Editor editor(config);
  editor.start();

  xe::shutdown();

  return 0;
}