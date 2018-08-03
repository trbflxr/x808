//
// Created by FLXR on 7/29/2018.
//

#ifndef X808_DUMMYPLAYERCOMPONENT_HPP
#define X808_DUMMYPLAYERCOMPONENT_HPP


#include <ecs/ecscomponent.hpp>
#include <gfx/camera.hpp>

struct DummyPlayerComponent : public xe::ECSComponent<DummyPlayerComponent> {
	xe::Camera *camera;

	float mouseSensitivity;
	float speed;
	float sprintSpeed;

	explicit DummyPlayerComponent(xe::Camera *camera, float mouseSensitivity = 0.15f,
	                              float speed = 4.0f, float sprintSpeed = 4.0f) :
			camera(camera),
			mouseSensitivity(mouseSensitivity),
			speed(speed),
			sprintSpeed(speed * sprintSpeed) { }

};


#endif //X808_DUMMYPLAYERCOMPONENT_HPP
