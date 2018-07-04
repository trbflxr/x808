//
// Created by FLXR on 7/2/2018.
//

#include "layer2d.hpp"
#include "application/application.hpp"

xe::gfx::Layer2D::Layer2D(const mat4 &projection) {
	const uint width = Application::getApplication().getWindowWidth();
	const uint height = Application::getApplication().getWindowHeight();

	renderer = new Renderer2D(width, height);
	camera = new OrthographicCamera(projection);
	renderer->setCamera(Layer2D::camera);
}

xe::gfx::Layer2D::~Layer2D() {
	delete renderer;
	delete camera;

	renderables.clear();
}

void xe::gfx::Layer2D::render() {
	renderer->begin();

	for (auto &&renderable : renderables) {
		renderer->submit(renderable);
	}

	renderer->end();
	renderer->flush();
}

xe::gfx::Renderable2D *xe::gfx::Layer2D::add(xe::gfx::Renderable2D *renderable) {
	renderables.push_back(renderable);
	return renderable;
}

bool xe::gfx::Layer2D::resize(uint width, uint height) {
	renderer->setScreenSize({width, height});
	return false;
}

