//
// Created by FLXR on 6/29/2018.
//

#include "application.hpp"

xe::Application *xe::Application::instance = nullptr;

xe::Application::Application(const xe::Config &config) :
		config(config),
		frameTime(0.0f) {

	instance = this;
}

xe::Application::~Application() {
	delete window;
	delete timer;
}

void xe::Application::init() {
	platformInit();
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
	float updateTick = 1000.0f / config.tps;

	uint frames = 0;
	uint updates = 0;

	TimeStep timeStep(timer->elapsedMillis());

	while (running) {

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
}

void xe::Application::tick() {

}

void xe::Application::update(const xe::TimeStep &ts) {

}

void xe::Application::render() {

}

void xe::Application::onEvent(xe::Event &event) {

}
