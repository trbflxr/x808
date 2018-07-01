//
// Created by FLXR on 6/29/2018.
//

#include "layer2d.hpp"
#include "application/application.hpp"


xe::gfx::Layer2D::Layer2D(const xe::mat4 &projectionMatrix) {
	const uint width = Application::getApplication().getWindowWidth();
	const uint height = Application::getApplication().getWindowHeight();

	renderer = new Renderer2D(width, height);
	scene = new Scene2D(projectionMatrix);
	renderer->setCamera(scene->getCamera());
}

xe::gfx::Layer2D::Layer2D(xe::gfx::Scene2D *scene) :
		scene(scene) {

	const uint width = Application::getApplication().getWindowWidth();
	const uint height = Application::getApplication().getWindowHeight();

	renderer = new Renderer2D(width, height);
	renderer->setCamera(scene->getCamera());
}

xe::gfx::Layer2D::~Layer2D() {
	delete renderer;
	delete scene;
}

void xe::gfx::Layer2D::init() {
	init(*renderer);
}

xe::gfx::Renderable2D *xe::gfx::Layer2D::submit(xe::gfx::Renderable2D *renderable) {
	submittedRenderables.push_back(renderable);
	return renderable;
}

xe::gfx::Sprite *xe::gfx::Layer2D::add(xe::gfx::Sprite *sprite) {
	scene->add(new Entity(sprite, math::translate(vec3(sprite->getPosition()))));
	return sprite;
}

void xe::gfx::Layer2D::render() {
	scene->render();

	renderer->begin();

	for (auto &&renderable : submittedRenderables) {
		renderable->submit(renderer);
	}

	render(*renderer);

	renderer->end();
	renderer->flush();

	submittedRenderables.clear();
}

bool xe::gfx::Layer2D::resize(uint width, uint height) {
	renderer->setScreenSize({width, height});
	scene->getRenderer()->setScreenSize({width, height});
	return false;
}
