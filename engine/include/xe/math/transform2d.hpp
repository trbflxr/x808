//
// Created by FLXR on 9/11/2018.
//

#ifndef X808_TRANSFORM2D_HPP
#define X808_TRANSFORM2D_HPP


#include <xe/math/math.hpp>

namespace xe {

	class Transform2D {
	public:
		inline Transform2D() :
				model(mat4::identity()),
				position(0.0f, 0.0f, 0.0f),
				rotation(0.0f),
				size(1.0f, 1.0f),
				dirty(true) { }


		inline explicit Transform2D(const vec3 &position, float rotationDeg, const vec2 &size) :
				model(mat4::identity()),
				position(position),
				rotation(rotationDeg),
				size(size),
				dirty(true) { }

		inline const mat4 &toMatrix() const;

		inline bool isDirty() const { return dirty; }
		inline void setDirty(bool isDirty) { dirty = isDirty; }

		inline const vec3 &getPosition() const { return position; }
		inline float getRotation() const { return rotation; }
		inline const vec2 &getSize() const { return size; }

		inline void setPosition(const vec3 &position) {
			Transform2D::position = position;
			dirty = true;
		}

		inline void setPosition(const vec2 &position) {
			Transform2D::position.x = position.x;
			Transform2D::position.y = position.y;
			dirty = true;
		}

		inline void setRotation(float angleDeg) {
			rotation = angleDeg;
			dirty = true;
		}

		inline void setSize(const vec2 &size) {
			Transform2D::size = size;
			dirty = true;
		}

		inline void rotate(float angleDeg);
		inline void move(const vec2 &dir);

	private:
		mutable mat4 model;
		mutable bool dirty;

		vec3 position;
		float rotation;
		vec2 size;
	};

	inline const mat4 &Transform2D::toMatrix() const {
		if (dirty) {
			model = mat4::transform(position, rotation);
			dirty = false;
		}
		return model;
	}

	inline void Transform2D::rotate(float angleDeg) {
		rotation = angleDeg;
		dirty = true;
	}

	inline void Transform2D::move(const vec2 &dir) {
		position.x += dir.x;
		position.y += dir.y;
		dirty = true;
	}

}


#endif //X808_TRANSFORM2D_HPP
