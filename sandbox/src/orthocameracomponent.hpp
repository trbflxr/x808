//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_ORTHOCAMERACOMPONENT_HPP
#define X808_ORTHOCAMERACOMPONENT_HPP


#include <xe/gfx/camera.hpp>
#include <xe/ecs/ecscomponent.hpp>

struct CameraComponent : public xe::ECSComponent<CameraComponent> {
	xe::Camera camera;

	explicit CameraComponent(const xe::mat4 &projection) : camera(projection) { }
};


#endif //X808_ORTHOCAMERACOMPONENT_HPP
