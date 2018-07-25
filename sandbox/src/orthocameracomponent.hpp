//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_ORTHOCAMERACOMPONENT_HPP
#define X808_ORTHOCAMERACOMPONENT_HPP


#include <gfx/camera/orthographiccamera.hpp>
#include <ecs/ecscomponent.hpp>


struct OrthoCameraComponent : public xe::ECSComponent<OrthoCameraComponent> {
	xe::gfx::OrthographicCamera camera;

	explicit OrthoCameraComponent(const xe::mat4 &projection) : camera(projection) { }
};


#endif //X808_ORTHOCAMERACOMPONENT_HPP
