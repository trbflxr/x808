//
// Created by FLXR on 6/30/2018.
//

#include "scene2d.hpp"
#include "application/application.hpp"

xe::gfx::Scene2D::Scene2D(const xe::mat4 &ortho) :
		camera(new OrthographicCamera(ortho)) {

	const uint width = Application::getApplication().getWindowWidth();
	const uint height = Application::getApplication().getWindowHeight();

	renderer = new Renderer2D(width, height);
	renderer->setCamera(camera);
}

xe::gfx::Scene2D::~Scene2D() {
	delete camera;
	delete renderer;
}

void xe::gfx::Scene2D::add(xe::Entity *entity) {
	entities.push_back(entity);
}

void xe::gfx::Scene2D::render() {
	camera->update();

	renderer->begin();

	for (auto &&e : entities) {
		SpriteComponent* spriteComponent = e->getComponent<SpriteComponent>();
		if(spriteComponent){
			TransformComponent* transformComponent = e->getComponent<TransformComponent>();
			XE_ASSERT(transformComponent, "Sprite does not have transform");

			spriteComponent->sprite->submit(renderer);
		}
	}

	render(*renderer);

	renderer->end();
	renderer->flush();
}
