//
// Created by FLXR on 7/26/2018.
//

#ifndef X808_GAMEOBJECT_HPP
#define X808_GAMEOBJECT_HPP


#include <xe/math/itransformable.hpp>

namespace xe {

	class GameObject : public ITransformable {
	public:
		GameObject() = default;

		explicit GameObject(const mat4 &transformation) :
				ITransformable(transformation) { }

		~GameObject() override = default;
	};

}


#endif //X808_GAMEOBJECT_HPP
