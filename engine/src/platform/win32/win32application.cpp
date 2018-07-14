//
// Created by FLXR on 7/6/2018.
//

#include "application/application.hpp"
#include "gfx/renderer.hpp"
#include "utils/random.hpp"
#include "resources/fontmanager.hpp"
#include "resources/texturemanager.hpp"

namespace xe {

	Application::Application(const Config &config, gfx::api::RenderAPI api) :
			config(config),
			frameTime(0.0f) {

		//init random
		random::nextInt32(0, 1);

		gfx::api::Context::setRenderAPI(api);
		instance = this;
	}

	Application::~Application() {
		delete window;
	}

	void Application::platformInit() {
		WindowProperties props;
		props.width = config.width;
		props.height = config.height;
		props.title = config.title;
		props.vSync = config.vSync;
		props.fullScreen = config.fullScreen;

		window = new Window(props);
		window->setEventCallback(METHOD(&Application::onEvent));
	}

	void Application::start() {
		init();
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

		const float MS_PER_TICK = 1.0f / config.ups;

		uint tickCount = 0;
		uint frames = 0;

		float time = 0.0f;

		float lastTime = timer.elapsed();
		float tickLag = 0;

		while (running) {
			gfx::Renderer::resetDC();

			float currentTime = timer.elapsed();
			float delta = currentTime - lastTime;

			lastTime = currentTime;
			tickLag += delta;

			while (tickLag >= MS_PER_TICK) {
				++tickCount;

				fixedUpdate(delta);

				tickLag -= MS_PER_TICK;
			}

			update(delta);

			window->clear();

			Timer frameTimer;
			render();
			frames++;
			frameTime = frameTimer.elapsedMillis();

			window->update();
			if (timer.elapsed() - time > 1.0f) {
				time += 1.0f;
				fps = frames;
				ups = tickCount;
				frames = 0;
				tickCount = 0;

				tick();
			}

			if (window->shouldClose()) running = false;
		}

		FontManager::clean();
		TextureManager::clean();
	}

}