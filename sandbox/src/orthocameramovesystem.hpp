//
// Created by FLXR on 7/24/2018.
//

#ifndef X808_ORTHOCAMERAMOVESYSTEM_HPP
#define X808_ORTHOCAMERAMOVESYSTEM_HPP


#include <gfx/renderer2d.hpp>
#include <ecs/ecssystem.hpp>
#include <window/keyboard.hpp>
#include "orthocameracomponent.hpp"

class OrthoCameraMoveSystem : public xe::BaseECSSystem {
public:
	explicit OrthoCameraMoveSystem(xe::gfx::Renderer2D *renderer) : BaseECSSystem(), renderer(renderer) {
		addComponentType(CameraComponent::ID);
	}

	void updateComponents(float delta, xe::BaseECSComponent **components) override {
		CameraComponent *camera = (CameraComponent *) components[0];

		xe::vec3 pos = camera->camera.transform.getTranslation();

		if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::D)) {
			pos.x += 100 * delta;
		}
		if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::A)) {
			pos.x -= 100 * delta;
		}
		if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::W)) {
			pos.y += 100 * delta;
		}
		if (xe::Keyboard::isKeyPressed(xe::Keyboard::Key::S)) {
			pos.y -= 100 * delta;
		}
		camera->camera.transform.setTranslation(pos);

		camera->camera.update();

		renderer->setCamera(&camera->camera);
	}

private:
	xe::gfx::Renderer2D *renderer;
};

#endif //X808_ORTHOCAMERAMOVESYSTEM_HPP
