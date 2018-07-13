//
// Created by FLXR on 6/28/2018.
//

#include <FreeImage.h>

#include "window.hpp"
#include "utils/log.hpp"
#include "resources/soundmanager.hpp"
#include "gfx/renderer.hpp"


std::map<void *, xe::Window *> xe::Window::handles;

xe::Window::Window(const xe::WindowProperties &props) :
		props(props), closed(false), eventCallback(nullptr) {

	if (!init()) {
		XE_FATAL("Window initialization failed");
		return;
	}

	FreeImage_Initialise();

	SoundManager::init();
	inputManager = new InputManager();
}

xe::Window::~Window() { }

bool xe::Window::init() {
	if (!platformInit()) {
		XE_FATAL("Failed to initialize platform");
		return false;
	}

	gfx::Renderer::init();

	setTitle(props.title);

	return true;
}

void xe::Window::clear() const {
	gfx::Renderer::clear(gfx::RENDERER_BUFFER_COLOR | gfx::RENDERER_BUFFER_DEPTH);
}

void xe::Window::update() {
	platformUpdate();

	SoundManager::update();

	inputManager->update();
}

void xe::Window::setEventCallback(const xe::WindowEventCallback &callback) {
	eventCallback = callback;
	inputManager->setEventCallback(callback);
}

void xe::Window::registerWindowClass(void *handle, xe::Window *window) {
	handles[handle] = window;
}

xe::Window *xe::Window::getWindowClass(void *handle) {
	return handle == nullptr ? handles.begin()->second : handles[handle];
}