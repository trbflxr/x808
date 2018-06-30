//
// Created by FLXR on 6/29/2018.
//

#include "layer2d.hpp"
#include "application/application.hpp"

//todo: remove
#include "gfx/api/texture2d.hpp"

xe::gfx::Layer2D::Layer2D(const xe::mat4 &projectionMatrix) {
	const uint width = Application::getApplication().getWindowWidth();
	const uint height = Application::getApplication().getWindowHeight();

	renderer = new Renderer2D(width, height);


	//todo: remove
	api::TextureParameters params(api::TextureFilter::NEAREST);

	dummy = new Renderable2D();
	dummy->texture = new api::Texture2D("test1", "assets/textures/test1.png", params);

	api::Texture::setWrap(api::TextureWrap::CLAMP_TO_BORDER);
}

xe::gfx::Layer2D::~Layer2D() {
	delete dummy->texture;
	delete dummy;
}

void xe::gfx::Layer2D::init() {
	init(*renderer);
}

void xe::gfx::Layer2D::init(xe::gfx::Renderer2D &renderer) {

}

void xe::gfx::Layer2D::render() {
	renderer->begin();

	renderer->drawLine(0, 0, 100, 100, color::CYAN, 0.1f);
	renderer->fillRect({-15, -5}, {5, 5}, color::PINK);

	renderer->submit(dummy);

	renderer->end();
	renderer->flush();

	render(*renderer);
}

void xe::gfx::Layer2D::render(xe::gfx::Renderer2D &renderer) {

}

bool xe::gfx::Layer2D::resize(uint width, uint height) {
	return false;
}
