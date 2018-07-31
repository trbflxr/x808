//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_TRANSFORM_HPP
#define X808_TRANSFORM_HPP


#include "math.hpp"

namespace xe {

	class Transform {
	public:
		inline Transform() :
				translation(0.0f, 0.0f, 0.0f),
				rotation(0.0f, 0.0f, 0.0f, 1.0f),
				scale(1.0f, 1.0f, 1.0f),
				dirty(false) { }

		inline Transform(const vec3 &translation) :
				translation(translation),
				rotation(0.0f, 0.0f, 0.0f, 1.0f),
				scale(1.0f, 1.0f, 1.0f),
				dirty(false) { }

		inline Transform(const quat &rotation) :
				translation(0.0f, 0.0f, 0.0f),
				rotation(rotation),
				scale(1.0f, 1.0f, 1.0f),
				dirty(false) { }

		inline Transform(const vec3 &translation, const quat &rotation, const vec3 &scale) :
				translation(translation),
				rotation(rotation),
				scale(scale),
				dirty(false) { }

		inline mat4 toMatrix() const;

		inline bool isDirty() const { return dirty; }
		inline void setDirty(bool isDirty) { dirty = isDirty; }

		inline vec3 getTranslation() const { return translation; }
		inline quat getRotation() const { return rotation; }
		inline vec3 getScale() const { return scale; }

		inline void set(const vec3 &translation, const quat &rotation, const vec3 &scale) {
			Transform::translation = translation;
			Transform::rotation = rotation;
			Transform::scale = scale;
			dirty = true;
		}

		inline void setTranslation(const vec3 &translation) {
			Transform::translation = translation;
			dirty = true;
		}

		inline void setRotation(const quat &rotation) {
			Transform::rotation = rotation;
			dirty = true;
		}

		inline void setScale(const vec3 &scale) {
			Transform::scale = scale;
			dirty = true;
		}

		inline void rotate(const vec3 &axis, float angleDeg);
		inline void rotate(const quat &rotation);
		inline void translate(const vec3 &dir);

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

		bool dirty;
	};

	inline mat4 Transform::toMatrix() const {
		return mat4::transform(translation, rotation, scale);
	}

	inline void Transform::rotate(const vec3 &axis, float angleDeg) {
		rotate(quat(axis, angleDeg));
	}

	inline void Transform::rotate(const quat &rotation) {
		Transform::rotation = quat::normalize(rotation * Transform::rotation);
		dirty = true;
	}

	inline void Transform::translate(const vec3 &dir) {
		translation += dir;
		dirty = true;
	}

	Transform Transform::operator+(const Transform &other) const {
		return Transform(translation + other.translation, rotation + other.rotation, scale + other.scale);
	}

	Transform Transform::operator+=(const Transform &other) {
		translation += other.translation;
		rotation += other.rotation;
		scale += other.scale;
		dirty = true;
		return *this;
	}

	Transform Transform::operator*(const Transform &other) const {
		return Transform(translation * other.translation, rotation * other.rotation, scale * other.scale);
	}

	Transform Transform::operator*=(const Transform &other) {
		translation *= other.translation;
		rotation *= other.rotation;
		scale *= other.scale;
		dirty = true;
		return *this;
	}

	Transform Transform::operator*(float other) const {
		return Transform(translation * other, rotation * other, scale * other);
	}

	Transform Transform::operator*=(float other) {
		translation *= other;
		rotation *= other;
		scale *= other;
		dirty = true;
		return *this;
	}

}


#endif //X808_TRANSFORM_HPP
