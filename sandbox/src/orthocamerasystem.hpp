//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_CAMERASYSTEM_HPP
#define X808_CAMERASYSTEM_HPP


#include <gfx/renderer2d.hpp>
#include <ecs/ecssystem.hpp>
#include "orthocameracomponent.hpp"


class OrthoCameraSystem : public xe::BaseECSSystem {
public:
	explicit OrthoCameraSystem(xe::gfx::Renderer2D *renderer) : BaseECSSystem(), renderer(renderer) {
		addComponentType(OrthoCameraComponent::ID);
	}

	void updateComponents(float delta, xe::BaseECSComponent **components) override {
		OrthoCameraComponent *camera = (OrthoCameraComponent *) components[0];

		//temp solution
		xe::vec3 pos = camera->camera.getPosition();

		if (xe::Input::isKeyPressed(XE_KEY_A)) {
			pos.x += 1;
		}
		if (xe::Input::isKeyPressed(XE_KEY_D)) {
			pos.x -= 1;
		}
		if (xe::Input::isKeyPressed(XE_KEY_W)) {
			pos.y -= 1;
		}
		if (xe::Input::isKeyPressed(XE_KEY_S)) {
			pos.y += 1;
		}
		camera->camera.setPosition(pos);

		camera->camera.update();

		renderer->setCamera(&camera->camera);
	}

private:
	xe::gfx::Renderer2D *renderer;
};


#endif //X808_CAMERASYSTEM_HPP
