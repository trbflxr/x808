//
// Created by FLXR on 7/26/2018.
//

#ifndef X808_GAMEOBJECT_HPP
#define X808_GAMEOBJECT_HPP


#include <xe/math/transform.hpp>

namespace xe {

	struct GameObject {
		Transform transform;

		GameObject() = default;

		explicit GameObject(const mat4 &transformation) :
				transform(transformation) { }

		virtual ~GameObject() = default;
	};

}


#endif //X808_GAMEOBJECT_HPP
