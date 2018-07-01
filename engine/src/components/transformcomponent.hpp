//
// Created by FLXR on 7/1/2018.
//

#ifndef X808_TRANSFORMCOMPONENT_HPP
#define X808_TRANSFORMCOMPONENT_HPP


#include "component.hpp"
#include "math/mat4.hpp"

namespace xe {

	class TransformComponent : public Component {
	public:
		explicit TransformComponent(const mat4 &transform) : transform(transform) { }

		static const char *getStaticType() {
			static const char *type ="Transform";
			return type;
		}

		inline const char *getType() const override { return getStaticType(); }

	public:
		mat4 transform;
	};

}


#endif //X808_TRANSFORMCOMPONENT_HPP
