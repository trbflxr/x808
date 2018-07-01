//
// Created by FLXR on 7/2/2018.
//

#include "layer2d.hpp"
#include "application/application.hpp"

xe::gfx::Layer2D::Layer2D(const xe::mat4 &projection, xe::gfx::api::Shader *shader) :
		shader(shader) {

	root = new GameObject();

	const uint width = Application::getApplication().getWindowWidth();
	const uint height = Application::getApplication().getWindowHeight();

	renderer = new Renderer2D(width, height);
	camera = new OrthographicCamera(projection);
	renderer->setCamera(camera);
}

xe::gfx::Layer2D::~Layer2D() {
	delete renderer;
	delete camera;
}

void xe::gfx::Layer2D::render() {
	renderer->begin();

	root->render(shader);

	renderer->end();
	renderer->flush();
}

bool xe::gfx::Layer2D::resize(uint width, uint height) {
	renderer->setScreenSize({width, height});
	return false;
}

