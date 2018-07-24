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

		renderer->setCamera(&camera->camera);
	}

private:
	xe::gfx::Renderer2D *renderer;
};


#endif //X808_CAMERASYSTEM_HPP
