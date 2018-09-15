//
// Created by FLXR on 9/13/2018.
//

#ifndef X808_ITRANSFORMABLE2D_HPP
#define X808_ITRANSFORMABLE2D_HPP


#include <xe/math/math.hpp>

namespace xe {

	class ITransformable2D {
	public:
		inline ITransformable2D() :
				position(0.0f, 0.0f, 0.0f),
				size(1.0f, 1.0f),
				rotation(0.0f),
				dirty(true) { }


		inline explicit ITransformable2D(const vec3 &position, const vec2 &size, float rotationDeg = 0.0f) :
				position(position),
				size(size),
				rotation(rotationDeg),
				dirty(true) { }

		inline void set(const vec3 &position, const vec2 &size, float angleDeg = 0.0f);

		inline bool isDirty() const { return dirty; }
		inline void setDirty(bool isDirty) const { dirty = isDirty; }

		inline const vec3 &getPosition() const { return position; }
		inline float getRotation() const { return rotation; }
		inline const vec2 &getSize() const { return size; }

		inline void setPosition(const vec3 &position) {
			ITransformable2D::position = position;
			dirty = true;
		}

		inline void setPosition(const vec2 &position) {
			ITransformable2D::position.x = position.x;
			ITransformable2D::position.y = position.y;
			dirty = true;
		}

		inline void setRotation(float angleDeg) {
			rotation = angleDeg;
			dirty = true;
		}

		inline void setSize(const vec2 &size) {
			ITransformable2D::size = size;
			dirty = true;
		}

		inline void rotate(float angleDeg);
		inline void move(const vec2 &dir);

	private:
		mutable bool dirty;

		vec3 position;
		float rotation;
		vec2 size;
	};


	void ITransformable2D::set(const vec3 &position, const vec2 &size, float angleDeg) {
		ITransformable2D::position = position;
		ITransformable2D::size = size;
		rotation = angleDeg;
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

	inline void ITransformable2D::move(const vec2 &dir) {
		position.x += dir.x;
		position.y += dir.y;
		dirty = true;
	}

}


#endif //X808_ITRANSFORMABLE2D_HPP
