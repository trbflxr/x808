//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_TRANSFORM_HPP
#define X808_TRANSFORM_HPP


#include <xe/math/math.hpp>

namespace xe {

	class Transform {
	public:
		inline Transform() :
				transformation(mat4::identity()),
				position(0.0f, 0.0f, 0.0f),
				rotation(0.0f, 0.0f, 0.0f, 1.0f),
				scale(1.0f, 1.0f, 1.0f),
				dirty(false) { }

		inline explicit Transform(const mat4 &transformation) :
				transformation(transformation),
				position(transformation.getTranslation()),
				scale(transformation.getScale()),
				rotation(transformation.getRotation()),
				dirty(true) { }

		inline explicit Transform(const vec3 &translation) :
				transformation(mat4::identity()),
				position(translation),
				rotation(0.0f, 0.0f, 0.0f, 1.0f),
				scale(1.0f, 1.0f, 1.0f),
				dirty(false) { }

		inline explicit Transform(const quat &rotation) :
				transformation(mat4::identity()),
				position(0.0f, 0.0f, 0.0f),
				rotation(rotation),
				scale(1.0f, 1.0f, 1.0f),
				dirty(false) { }

		inline explicit Transform(const vec3 &translation, const quat &rotation, const vec3 &scale) :
				transformation(mat4::identity()),
				position(translation),
				rotation(rotation),
				scale(scale),
				dirty(false) { }

		inline const mat4 &toMatrix() const;

		inline bool isDirty() const { return dirty; }
		inline void setDirty(bool isDirty) { dirty = isDirty; }

		inline vec3 getPosition() const { return position; }
		inline quat getRotation() const { return rotation; }
		inline vec3 getScale() const { return scale; }

		inline void set(const vec3 &position, const quat &rotation, const vec3 &scale) {
			Transform::position = position;
			Transform::rotation = rotation;
			Transform::scale = scale;
			dirty = true;
		}

		inline void setPosition(const vec3 &position) {
			Transform::position = position;
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
		inline void move(const vec3 &dir);

		inline Transform operator+(const Transform &other) const;
		inline Transform operator+=(const Transform &other);
		inline Transform operator*(const Transform &other) const;
		inline Transform operator*=(const Transform &other);
		inline Transform operator*(float other) const;
		inline Transform operator*=(float other);

	private:
		mutable mat4 transformation;
		mutable bool dirty;

		vec3 position;
		quat rotation;

		vec3 scale;
	};

	inline const mat4 &Transform::toMatrix() const {
		if (dirty) {
			transformation = mat4::transform(position, rotation, scale);
			dirty = false;
		}
		return transformation;
	}

	inline void Transform::rotate(const vec3 &axis, float angleDeg) {
		rotate(quat(axis, angleDeg));
	}

	inline void Transform::rotate(const quat &rotation) {
		Transform::rotation = quat::normalize(rotation * Transform::rotation);
		dirty = true;
	}

	inline void Transform::move(const vec3 &dir) {
		position += dir;
		dirty = true;
	}

	Transform Transform::operator+(const Transform &other) const {
		return Transform(position + other.position, rotation + other.rotation, scale + other.scale);
	}

	Transform Transform::operator+=(const Transform &other) {
		position += other.position;
		rotation += other.rotation;
		scale += other.scale;
		dirty = true;
		return *this;
	}

	Transform Transform::operator*(const Transform &other) const {
		return Transform(position * other.position, rotation * other.rotation, scale * other.scale);
	}

	Transform Transform::operator*=(const Transform &other) {
		position *= other.position;
		rotation *= other.rotation;
		scale *= other.scale;
		dirty = true;
		return *this;
	}

	Transform Transform::operator*(float other) const {
		return Transform(position * other, rotation * other, scale * other);
	}

	Transform Transform::operator*=(float other) {
		position *= other;
		rotation *= other;
		scale *= other;
		dirty = true;
		return *this;
	}

}


#endif //X808_TRANSFORM_HPP
