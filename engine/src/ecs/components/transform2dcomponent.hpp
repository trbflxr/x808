//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_TRANSFORM2DCOMPONENT_HPP
#define X808_TRANSFORM2DCOMPONENT_HPP


#include "ecs/ecscomponent.hpp"
#include "math/aobb.hpp"

namespace xe {

	struct Transform2DComponent : public ECSComponent<Transform2DComponent> {
		aobb bounds;
		float zIndex;
	};

}


#endif //X808_TRANSFORM2DCOMPONENT_HPP
