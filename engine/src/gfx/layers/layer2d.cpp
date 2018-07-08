//
// Created by FLXR on 7/2/2018.
//

#include "layer2d.hpp"
#include "application/application.hpp"

xe::gfx::Layer2D::Layer2D() {
	const uint width = Application::getApplication().getWindowWidth();
	const uint height = Application::getApplication().getWindowHeight();

	renderer = new Renderer2D(width, height);
}

xe::gfx::Layer2D::~Layer2D() {
	delete renderer;
}

bool xe::gfx::Layer2D::resize(uint width, uint height) {
	renderer->setScreenSize({width, height});
	return false;
}

