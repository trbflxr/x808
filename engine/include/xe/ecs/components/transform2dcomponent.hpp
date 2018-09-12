//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_TRANSFORM2DCOMPONENT_HPP
#define X808_TRANSFORM2DCOMPONENT_HPP


#include <xe/ecs/ecscomponent.hpp>
#include <xe/math/transform2d.hpp>

namespace xe {

	struct Transform2DComponent : public ECSComponent<Transform2DComponent> {
		Transform2D transform;

		explicit Transform2DComponent(const vec3 &position, const vec2 &size, float rotation = 0.0f) :
				transform(position, size, rotation) { }
	};

}


#endif //X808_TRANSFORM2DCOMPONENT_HPP
