//
// Created by FLXR on 7/1/2018.
//

#ifndef X808_TRANSFORM_HPP
#define X808_TRANSFORM_HPP


#include "common.hpp"
#include "math/math.hpp"

namespace xe {

	class XE_API Transform {
	public:
		explicit Transform();

		void move(const vec3 &direction);
		void rotate(float deg, const vec3 &axis);

		void lookAt(const vec3 &point, const vec3 &up);
		quat getLookAtRotation(const vec3 &point, const vec3 &up) const;

		mat4 getTransformation() const;

		inline vec3 getTransformedPos() const { return getParentMatrix().transform(position); }
		quat getTransformedRot() const;

		inline const vec3 &getPosition() const { return position; }
		inline void setPosition(const vec3 &position) { Transform::position = position; }

		inline const quat &getRotation() const { return rotation; }
		inline void setRotation(const quat &rotation) { Transform::rotation = rotation; }

		inline const vec3 &getScale() const { return scale; }
		inline void setScale(const vec3 &scale) { Transform::scale = scale; }

		inline void setParent(Transform *parent) { Transform::parent = parent; }

	private:
		mat4 getParentMatrix() const;

	private:
		Transform *parent;

		vec3 position;
		quat rotation;
		vec3 scale;
	};

}


#endif //X808_TRANSFORM_HPP
