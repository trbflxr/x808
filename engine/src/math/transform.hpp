//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_TRANSFORM_HPP
#define X808_TRANSFORM_HPP


#include "vec3.hpp"
#include "quat.hpp"
#include "mat4.hpp"

namespace xe {

	class Transform {
	public:
		inline Transform() :
				translation(0.0f, 0.0f, 0.0f),
				rotation(0.0f, 0.0f, 0.0f, 1.0f),
				scale(1.0f, 1.0f, 1.0f) { }

		inline Transform(const vec3 &translation) :
				translation(translation),
				rotation(0.0f, 0.0f, 0.0f, 1.0f),
				scale(1.0f, 1.0f, 1.0f) { }

		inline Transform(const quat &rotation) :
				translation(0.0f, 0.0f, 0.0f),
				rotation(rotation),
				scale(1.0f, 1.0f, 1.0f) { }

		inline Transform(const vec3 &translation, const quat &rotation, const vec3 &scale) :
				translation(translation),
				rotation(rotation),
				scale(scale) { }

		inline mat4 toMatrix() const;

		inline vec3 getTranslation() const { return translation; }
		inline quat getRotation() const { return rotation; }
		inline vec3 getScale() const { return scale; }

		inline void set(const vec3 &translation, const quat &rotation, const vec3 &scale) {
			Transform::translation = translation;
			Transform::rotation = rotation;
			Transform::scale = scale;
		}

		inline void setTranslation(const vec3 &translation) { Transform::translation = translation; }
		inline void setRotation(const quat &rotation) { Transform::rotation = rotation; }
		inline void setScale(const vec3 &scale) { Transform::scale = scale; }


		inline Transform operator+(const Transform &other) const;
		inline Transform operator+=(const Transform &other);
		inline Transform operator*(const Transform &other) const;
		inline Transform operator*=(const Transform &other);
		inline Transform operator*(float other) const;
		inline Transform operator*=(float other);

	private:
		vec3 translation;
		quat rotation;
		vec3 scale;
	};

	inline mat4 Transform::toMatrix() const {
		//todo: create
	}

	Transform Transform::operator+(const Transform &other) const {
		return Transform(translation + other.translation, rotation + other.rotation, scale + other.scale);
	}

	Transform Transform::operator+=(const Transform &other) {
		translation += other.translation;
		rotation += other.rotation;
		scale += other.scale;
		return *this;
	}

	Transform Transform::operator*(const Transform &other) const {
		return Transform(translation * other.translation, rotation * other.rotation, scale * other.scale);
	}

	Transform Transform::operator*=(const Transform &other) {
		translation *= other.translation;
		rotation *= other.rotation;
		scale *= other.scale;
		return *this;
	}

	Transform Transform::operator*(float other) const {
		return Transform(translation * other, rotation * other, scale * other);
	}

	Transform Transform::operator*=(float other) {
		translation *= other;
		rotation *= other;
		scale *= other;
		return *this;
	}

}


#endif //X808_TRANSFORM_HPP
