#include <xe/app/application.hpp>
#include <xe/core/vfs.hpp>
#include <xe/core/filesystem.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/resources/soundmanager.hpp>
#include "mainmenu.hpp"
#include "3d/examplescene.hpp"


static void writeKeyValue(xe::Config &config, const char *key, const char *value) {
  if (strcmp(key, "width") == 0) {
    config.width = (uint) atoi(value);
  } else if (strcmp(key, "height") == 0) {
    config.height = (uint) atoi(value);
  } else if (strcmp(key, "fullScreen") == 0) {
    config.fullScreen = (uint) atoi(value);
  } else if (strcmp(key, "vSync") == 0) {
    config.vSync = (bool) atoi(value);
  } else if (strcmp(key, "tickRate") == 0) {
    config.tickRate = (uint) atoi(value);
  } else if (strcmp(key, "maxFps") == 0) {
    config.maxFps = (uint) atoi(value);
  } else if (strcmp(key, "srgb") == 0) {
    config.srgb = (bool) atoi(value);
  } else if (strcmp(key, "renderApi") == 0) {
    config.renderApi = xe::stringToRenderApi(value);
  } else if (strcmp(key, "apiVersion") == 0) {
    config.apiVersion = (uint) atoi(value);
  } else if (strcmp(key, "maxSpotShadows") == 0) {
    config.maxSpotShadows = (uint) atoi(value);
  } else if (strcmp(key, "maxDirectionalCascades") == 0) {
    config.maxDirectionalCascades = (uint) atoi(value);
  } else if (strcmp(key, "shadowQuality") == 0) {
    config.shadowQuality = (uint) atoi(value);
  } else if (strcmp(key, "maxParallaxLayers") == 0) {
    config.maxParallaxLayers = (uint) atoi(value);
  }
}

static bool loadConfig(xe::Config &config, const char *path) {
  int64 size = xe::FileSystem::size(path);
  if (size == -1) return false;

  xe::string cfg(size, '\0');

  bool r = xe::FileSystem::read(path, &cfg[0], size);
  if (!r) return false;

  std::vector<xe::string> lines = xe::splitString(cfg, "\n\r");

  const char *search = "=";
  for (auto &&l : lines) {
    char *key = strtok(&l[0], search);
    char *value = strtok(nullptr, search);

    writeKeyValue(config, key, value);
  }

  return true;
}

class Test : public xe::Application {
public:
  explicit Test(const xe::Config &config) :
      Application(config, "Sandbox🌍") {

    xe::VFS::mount("fonts", "xe_sandbox_assets/fonts/");
    xe::VFS::mount("textures", "xe_sandbox_assets/textures/");
    xe::VFS::mount("audio", "xe_sandbox_assets/audio/");
    xe::VFS::mount("models", "xe_sandbox_assets/models/");
    xe::VFS::mount("shaders", "/");

    xe::TextureParameters params;
    xe::TextureManager::add(new xe::Texture("bg", "bg.png", params));
    xe::TextureManager::add(new xe::Texture("grass", "grass.png", params));
    xe::TextureManager::add(new xe::Texture("pepe", "feelsconflictedman.jpg", params));
    xe::TextureManager::add(new xe::Texture("test1", "test1.png", params));
    xe::TextureManager::add(new xe::Texture("test2", "test2.png", params));
    xe::TextureManager::add(new xe::Texture("test3", "test3.png", params));

    xe::TextureManager::add(new xe::TextureAtlas("atlas", "test.atlas", params));

    params.wrap = xe::TextureWrap::Repeat;
    xe::TextureManager::add(new xe::Texture("sp0", "sp0.png", params));

    xe::FontManager::add(new xe::Font("consolata72", "consolata.otf", 72.0f));
    xe::FontManager::add(new xe::Font("fogsans42", "fogsans.otf", 42.0f));
    xe::FontManager::add(new xe::Font("fogsansit72", "fogsansit.otf", 72.0f));
    xe::FontManager::add(new xe::Font("robotobold22", "robotobold.ttf", 22.0f));
    xe::FontManager::add(new xe::Font("robotoregular72", "robotoregular.ttf", 72.0f));

    xe::SoundManager::add(new xe::Sound("orunec", "orunec.wav"));

    ExampleScene::get().create();

    menu = new MainMenu();

    pushOverlay(menu);
  }

  ~Test() override {
    delete menu;

    ExampleScene::get().dispose();
  }

private:
  MainMenu *menu;
};

int main() {
  xe::initialize();

  xe::Config config;
  loadConfig(config, "xeconfig");

  Test test(config);
  test.start();

  xe::shutdown();

  return 0;
}
