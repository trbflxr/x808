//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_TRANSFORM2DCOMPONENT_HPP
#define X808_TRANSFORM2DCOMPONENT_HPP


#include <xe/ecs/ecscomponent.hpp>
#include <xe/math/aobb.hpp>

namespace xe {

	struct Transform2DComponent : public ECSComponent<Transform2DComponent> {
		aobb bounds;
		float zIndex;

		explicit Transform2DComponent(const vec2 &position, const vec2 &size, float zIndex, float rotation = 0.0f) :
				bounds(position, size, rotation),
				zIndex(zIndex) { }
	};

}


#endif //X808_TRANSFORM2DCOMPONENT_HPP
