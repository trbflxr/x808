//
// Created by FLXR on 7/25/2018.
//

#ifndef X808_TRANSFORMCOMPONENT_HPP
#define X808_TRANSFORMCOMPONENT_HPP


#include "ecs/ecscomponent.hpp"
#include "math/transform.hpp"

namespace xe {

	struct TransformComponent : public ECSComponent<TransformComponent> {
		Transform transform;

		TransformComponent() = default;
	};

}


#endif //X808_TRANSFORMCOMPONENT_HPP
