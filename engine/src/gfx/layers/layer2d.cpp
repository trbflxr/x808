//
// Created by FLXR on 6/29/2018.
//

#include "layer2d.hpp"
#include "application/application.hpp"


xe::gfx::Layer2D::Layer2D(const xe::mat4 &projectionMatrix) {
	const uint width = Application::getApplication().getWindowWidth();
	const uint height = Application::getApplication().getWindowHeight();

	renderer = new Renderer2D(width, height);
}

xe::gfx::Layer2D::~Layer2D() {
	delete renderer;
}

void xe::gfx::Layer2D::init() {
	init(*renderer);
}

void xe::gfx::Layer2D::init(xe::gfx::Renderer2D &renderer) {

}

xe::gfx::Renderable2D *xe::gfx::Layer2D::submit(xe::gfx::Renderable2D *renderable) {
	submittedRenderables.push_back(renderable);
	return renderable;
}

void xe::gfx::Layer2D::render() {
	renderer->begin();

	for (auto &&renderable : submittedRenderables) {
		renderable->submit(renderer);
	}

	render(*renderer);

	renderer->end();
	renderer->flush();
}

bool xe::gfx::Layer2D::resize(uint width, uint height) {
	return false;
}

