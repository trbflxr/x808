//
// Created by FLXR on 7/29/2018.
//

#ifndef X808_DUMMYPLAYERCOMPONENT_HPP
#define X808_DUMMYPLAYERCOMPONENT_HPP


#include <xe/ecs/ecscomponent.hpp>
#include <xe/gfx/camera.hpp>

struct DummyPlayerComponent : public xe::ECSComponent<DummyPlayerComponent> {
	xe::Camera *camera;

	float mouseSensitivity;
	float speed;
	float sprintSpeed;

	explicit DummyPlayerComponent(xe::Camera *camera,
	                              float speed = 4.0f,
	                              float sprint = 4.0f,
	                              float sensitivity = 0.15f) :
			camera(camera),
			mouseSensitivity(sensitivity),
			speed(speed),
			sprintSpeed(speed * sprint) { }

};


#endif //X808_DUMMYPLAYERCOMPONENT_HPP
