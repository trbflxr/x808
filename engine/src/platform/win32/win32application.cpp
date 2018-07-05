//
// Created by FLXR on 7/6/2018.
//

#include "application/application.hpp"
#include "gfx/renderer.hpp"
#include "resources/fontmanager.hpp"
#include "resources/texturemanager.hpp"

xe::Application::Application(const xe::Config &config, gfx::api::RenderAPI api) :
		config(config),
		frameTime(0.0f) {

	gfx::api::Context::setRenderAPI(api);
	instance = this;
}

xe::Application::~Application() {
	delete window;
	delete timer;
}

void xe::Application::platformInit() {
	xe::WindowProperties props;
	props.width = config.width;
	props.height = config.height;
	props.title = config.title;
	props.vSync = config.vSync;
	props.fullScreen = config.fullScreen;

	window = new Window(props);
	window->setEventCallback(METHOD(&Application::onEvent));
}

void xe::Application::start() {
	init();
	running = true;
	suspend_ = false;
	run();
}

void xe::Application::suspend() {
	suspend_ = true;
}

void xe::Application::resume() {
	suspend_ = false;
}

void xe::Application::stop() {
	running = false;
}

void xe::Application::run() {
	timer = new Timer();
	float time = 0.0f;

	float updateTimer = timer->elapsed();
	float updateTick = 1000.0f / config.ups;

	uint frames = 0;
	uint updates = 0;

	TimeStep timeStep(timer->elapsedMillis());

	while (running) {
		gfx::Renderer::resetDC();

		window->clear();

		float now = timer->elapsedMillis();

		if (now - updateTimer > updateTick) {
			timeStep.update(now);

			update(timeStep);

			updates++;
			updateTimer += updateTick;
		}

		Timer frameTimer;
		render();
		frames++;
		frameTime = frameTimer.elapsedMillis();

		window->update();
		if (timer->elapsed() - time > 1.0f) {
			time += 1.0f;
			fps = frames;
			ups = updates;
			frames = 0;
			updates = 0;

			tick();
		}

		if (window->shouldClose()) running = false;
	}

	FontManager::clean();
	TextureManager::clean();
}