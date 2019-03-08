//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_ITRANSFORMABLE_HPP
#define X808_ITRANSFORMABLE_HPP


#include <xe/math/vec2.hpp>
#include <xe/math/vec4.hpp>
#include <xe/math/quat.hpp>
#include <xe/math/mat4.hpp>

namespace xe {

	class ITransformable {
	public:
		inline explicit ITransformable(bool allowScale = true) :
				transformation(mat4::identity()),
				dirty(true),
				allowScale(allowScale),
				position(0.0f, 0.0f, 0.0f),
				rotation(0.0f, 0.0f, 0.0f, 1.0f),
				scale(1.0f, 1.0f, 1.0f) { }

		inline explicit ITransformable(const mat4 &transformation, bool allowScale = true) :
				transformation(transformation),
				dirty(false),
				allowScale(allowScale),
				position(transformation.getTranslation()),
				rotation(transformation.getRotation()),
				scale(transformation.getScale()) { }

		inline explicit ITransformable(const vec3 &translation, bool allowScale = true) :
				transformation(mat4::identity()),
				dirty(true),
				allowScale(allowScale),
				position(translation),
				rotation(0.0f, 0.0f, 0.0f, 1.0f),
				scale(1.0f, 1.0f, 1.0f) { }

		inline explicit ITransformable(const quat &rotation, bool allowScale = true) :
				transformation(mat4::identity()),
				dirty(true),
				allowScale(allowScale),
				position(0.0f, 0.0f, 0.0f),
				rotation(rotation),
				scale(1.0f, 1.0f, 1.0f) { }

		inline explicit ITransformable(const vec3 &translation, const quat &rotation, const vec3 &scale) :
				transformation(mat4::identity()),
				dirty(true),
				allowScale(true),
				position(translation),
				rotation(rotation),
				scale(scale) { }

		virtual ~ITransformable() = default;

		inline const mat4 &toMatrix() const;

		inline bool isDirty() const { return dirty; }
		inline void setDirty(bool isDirty) const { dirty = isDirty; }

		inline const vec3 &getPosition() const { return position; }
		inline const quat &getRotation() const { return rotation; }
		inline const vec3 &getScale() const { return scale; }

		inline void set(const vec3 &position, const quat &rotation, const vec3 &scale) {
			ITransformable::position = position;
			ITransformable::rotation = rotation;
			ITransformable::scale = scale;
			dirty = true;
		}

		inline void set(const mat4 &transformation) {
			position = transformation.getTranslation();
			rotation = transformation.getRotation();
			scale = transformation.getScale();
			dirty = true;
		}

		inline void setPosition(const vec3 &position) {
			ITransformable::position = position;
			dirty = true;
		}

		inline void setRotation(const quat &rotation) {
			ITransformable::rotation = rotation;
			dirty = true;
		}

		inline void setScale(const vec3 &scale) {
			ITransformable::scale = scale;
			dirty = true;
		}

		inline void rotate(const vec3 &axis, float angleDeg);
		inline void rotate(const quat &rotation);
		inline void move(const vec3 &dir);

		inline ITransformable operator+(const ITransformable &other) const;
		inline ITransformable operator+=(const ITransformable &other);
		inline ITransformable operator*(const ITransformable &other) const;
		inline ITransformable operator*=(const ITransformable &other);
		inline ITransformable operator*(float other) const;
		inline ITransformable operator*=(float other);

	private:
		mutable mat4 transformation;
		mutable bool dirty;

		bool allowScale;
		vec3 position;
		quat rotation;
		vec3 scale;
	};

	inline const mat4 &ITransformable::toMatrix() const {
		if (dirty) {
			if (allowScale) {
				transformation = mat4::transform(position, rotation, scale);
			} else {
				transformation = mat4::translation(position) * mat4::rotation(rotation);
			}

			dirty = false;
		}
		return transformation;
	}

	inline void ITransformable::rotate(const vec3 &axis, float angleDeg) {
		rotate(quat(axis, angleDeg));
	}

	inline void ITransformable::rotate(const quat &rotation) {
		ITransformable::rotation = quat::normalize(rotation * ITransformable::rotation);
		dirty = true;
	}

	inline void ITransformable::move(const vec3 &dir) {
		position += dir;
		dirty = true;
	}

	ITransformable ITransformable::operator+(const ITransformable &other) const {
		return ITransformable(position + other.position, rotation + other.rotation, scale + other.scale);
	}

	ITransformable ITransformable::operator+=(const ITransformable &other) {
		position += other.position;
		rotation += other.rotation;
		scale += other.scale;
		dirty = true;
		return *this;
	}

	ITransformable ITransformable::operator*(const ITransformable &other) const {
		return ITransformable(position * other.position, rotation * other.rotation, scale * other.scale);
	}

	ITransformable ITransformable::operator*=(const ITransformable &other) {
		position *= other.position;
		rotation *= other.rotation;
		scale *= other.scale;
		dirty = true;
		return *this;
	}

	ITransformable ITransformable::operator*(float other) const {
		return ITransformable(position * other, rotation * other, scale * other);
	}

	ITransformable ITransformable::operator*=(float other) {
		position *= other;
		rotation *= other;
		scale *= other;
		dirty = true;
		return *this;
	}

}


#endif //X808_ITRANSFORMABLE_HPP
