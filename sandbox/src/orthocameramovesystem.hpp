//
// Created by FLXR on 7/24/2018.
//

#ifndef X808_ORTHOCAMERAMOVESYSTEM_HPP
#define X808_ORTHOCAMERAMOVESYSTEM_HPP


#include <xe/ecs/ecssystem.hpp>
#include <xe/window/keyboard.hpp>
#include "orthocameracomponent.hpp"

class OrthoCameraMoveSystem : public xe::BaseECSSystem {
public:
	explicit OrthoCameraMoveSystem() :
			BaseECSSystem() {

		addComponentType(CameraComponent::ID);
	}

	void updateComponents(float delta, xe::BaseECSComponent **components) override {
		CameraComponent *camera = (CameraComponent *) components[0];

		xe::vec3 pos = camera->camera.transform.getPosition();

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
		camera->camera.transform.setPosition(pos);

		camera->camera.update();
	}
};

#endif //X808_ORTHOCAMERAMOVESYSTEM_HPP
