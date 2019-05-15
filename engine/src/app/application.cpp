//
// Created by FLXR on 6/29/2018.
//

#include <xe/app/application.hpp>
#include <xe/utils/random.hpp>
#include <xe/utils/assert.hpp>
#include <xe/utils/sleep.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/fontmanager.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/resources/shadermanager.hpp>
#include <xe/systems/shell.hpp>
#include <xe/audio/audiomaster.hpp>
#include <app/layerstack.hpp>
#include <app/systemstack.hpp>
#include <xe/ui/imgui/imgui_impl_xe.hpp>

namespace xe {

  Application *Application::instance = nullptr;

  Application::Application(const Config &config, const string &title) :
      config(config) {

    XE_ASSERT(!instance, "[Application]: Only one application instance allowed!");

    const_cast<Config &>(Config::get()) = config;

    //init random
    random::next<int32>(0, 1);

    Context::setRenderAPI(config.renderApi, config.apiVersion);

    instance = this;

    init(title);
  }

  Application::~Application() {
    delete shell;
    delete layerStack;
    delete systemStack;
  }

  void Application::init(const string &title) {
    if (config.fullScreen) {
      window.create(VideoMode::getDesktopMode(), title, WindowStyle::Fullscreen);

    } else {
      VideoMode mode(config.width, config.height);
      window.create(mode, title, WindowStyle::Default);
    }

    window.setVerticalSyncEnabled(config.vSync);

    ShaderManager::init();
    FontManager::init();
    TextureManager::init();

    AudioMaster::initialize();

    ImGui::xe::init(window);
    ImGui::StyleColorsDark();

    shell = new Shell();
    shell->init();

    layerStack = new LayerStack(this);
    systemStack = new SystemStack();
  }

  void Application::shutdown() {
    ImGui::SaveIniSettingsToDisk("imgui.ini");
    ImGui::xe::shutdown();
  }

  void Application::start() {
    running = true;
    suspend_ = false;
    run();
  }

  void Application::suspend() {
    suspend_ = true;
  }

  void Application::resume() {
    suspend_ = false;
  }

  void Application::stop() {
    running = false;
  }

  void Application::run() {
    Timer timer;
    Timer frameTimer;

    const float MS_PER_TICK = 1.0f / config.tickRate;
    const float TARGET_FPS = 1.0f / (config.maxFps + 1);

    uint tickCount = 0;
    uint frames = 0;

    float lastTime = timer.elapsed();
    float time = 0.0f;
    float tickLag = 0.0f;

    while (running) {
      const float currentTime = timer.elapsed();
      const float delta = currentTime - lastTime;
      const float dt = delta / MS_PER_TICK;

      lastTime = currentTime;
      tickLag += delta;

      const float frameStart = frameTimer.elapsed();

      while (tickLag >= MS_PER_TICK) {
        ++tickCount;

        fixedUpdate(MS_PER_TICK);

        tickLag -= MS_PER_TICK;
      }

      update(dt);

      window.clear();
      Renderer::resetDC();

      render();
      frames++;

      window.update();

      processEvents();

      lateUpdate(dt);

      //limit fps
      const float frameEnd = frameTimer.elapsed() - frameStart;
      if (config.maxFps != 0 && TARGET_FPS > frameEnd) {
        sleep(static_cast<uint>((TARGET_FPS - frameEnd) * 1000));
      }

      if (timer.elapsed() - time > 1.0f) {
        time += 1.0f;
        fps = frames;
        tps = tickCount;
        frames = 0;
        tickCount = 0;
      }

      if (!window.isOpen()) running = false;
    }

    shutdown();
  }

  void Application::update(float delta) {
    ImGui::xe::update(window, delta / config.tickRate);

    shell->update(delta);

    systemStack->update(delta);
    layerStack->update(delta);
  }

  void Application::lateUpdate(float delta) {
    systemStack->lateUpdate(delta);
    layerStack->lateUpdate(delta);
  }

  void Application::fixedUpdate(float delta) {
    systemStack->fixedUpdate(delta);
    layerStack->fixedUpdate(delta);
  }

  void Application::render() {
    ImGui::xe::newFrame();

    layerStack->render(!shell->isActive());
    systemStack->render();

    shell->render();

    ImGui::xe::render();
  }

  void Application::processEvents() {
    xe::Event event{ };

    while (window.pollEvent(event)) {

      ImGui::xe::processEvent(event);

      shell->input(event);

      systemStack->input(event);
      layerStack->input(event);

      if (event.type == Event::Closed) {
        window.close();
        break;
      }
    }
  }

  Layer *Application::getCurrentLayer() {
    return layerStack->getCurrentLayer();
  }

  void Application::pushLayer(Layer *layer) {
    layerStack->pushLayer(layer);
  }

  Layer *Application::popLayer() {
    return layerStack->popLayer();
  }

  void Application::pushOverlay(Layer *overlay) {
    layerStack->pushOverlay(overlay);
  }

  Layer *Application::popOverlay() {
    return layerStack->popOverlay();
  }

  void Application::pushSystem(System *system) {
    systemStack->pushSystem(system);
  }

  System *Application::popSystem() {
    return systemStack->popSystem();
  }

  void Application::setMaxFps(uint fps) {
    const_cast<Config &>(Config::get()).maxFps = fps;
    config.maxFps = fps;
  }

}