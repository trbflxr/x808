//
// Created by FLXR on 9/13/2018.
//

#ifndef X808_ITRANSFORMABLE2D_HPP
#define X808_ITRANSFORMABLE2D_HPP


#include <xe/math/vec2.hpp>
#include <xe/math/mat4.hpp>
#include <xe/math/mathfunc.hpp>

namespace xe {

	class ITransformable2D {
	public:
		inline ITransformable2D() :
				position(0.0f, 0.0f),
				rotation(0.0f),
				scale_(1.0f, 1.0f),
				origin(0.0f, 0.0f),
				dirty(true),
				model(mat4::identity()) { }


		inline explicit ITransformable2D(const vec2 &position, float rotationDeg = 0.0f) :
				position(position),
				rotation(rotationDeg),
				scale_(1.0f, 1.0f),
				origin(0.0f, 0.0f),
				dirty(true),
				model(mat4::identity()) { }

		inline void transformation(const vec2 &position, float angleDeg = 0.0f);

		inline bool isDirty() const { return dirty; }
		inline void setDirty(bool isDirty) const { dirty = isDirty; }

		inline const vec2 &getScale() const { return scale_; }
		inline const vec2 &getPosition() const { return position; }
		inline float getRotation() const { return rotation; }
		inline const vec2 &getOrigin() const { return origin; }

		inline void setPosition(const vec2 &position) {
			ITransformable2D::position = position;
			dirty = true;
		}

		inline void setRotation(float angleDeg) {
			ITransformable2D::rotation = angleDeg;
			dirty = true;
		}

		inline void setScale(const vec2 &scale) {
			ITransformable2D::scale_ = scale;
			dirty = true;
		}

		inline void setOrigin(const vec2 &origin) {
			ITransformable2D::origin = origin;
			dirty = true;
		}

		inline void move(const vec2 &dir);
		inline void rotate(float angleDeg);
		inline void scale(const vec2 &factor);

		inline const mat4 &toMatrix() const;

	private:
		vec2 position;
		float rotation;
		vec2 scale_;
		vec2 origin;

		mutable bool dirty;
		mutable mat4 model;
	};


	void ITransformable2D::transformation(const vec2 &position, float angleDeg) {
		ITransformable2D::position = position;
		rotation = angleDeg;
		dirty = true;
	}

	inline void ITransformable2D::move(const vec2 &dir) {
		position.x += dir.x;
		position.y += dir.y;
		dirty = true;
	}

	inline void ITransformable2D::rotate(float angleDeg) {
		rotation += angleDeg;

		if (rotation < -360.0f) {
			rotation += 360.0f;
		} else if (rotation > 360.0f) {
			rotation -= 360.0f;
		}

		dirty = true;
	}

	inline void ITransformable2D::scale(const vec2 &factor) {
		scale_ += factor;
		dirty = true;
	}

	const mat4 &ITransformable2D::toMatrix() const {
		if (dirty) {
			dirty = false;

			const float c = cosf(to_rad(-rotation));
			const float s = sinf(to_rad(-rotation));
			const float sxc = scale_.x * c;
			const float syc = scale_.y * c;
			const float sxs = scale_.x * s;
			const float sys = scale_.y * s;
			const float tx = -origin.x * sxc - origin.y * sys + position.x;
			const float ty = origin.x * sxs - origin.y * syc + position.y;

			model.rows[0].x = sxc;
			model.rows[0].y = sys;
			model.rows[0].w = tx;

			model.rows[1].x = -sxs;
			model.rows[1].y = syc;
			model.rows[1].w = ty;
		}

		return model;
	}

}


#endif //X808_ITRANSFORMABLE2D_HPP
