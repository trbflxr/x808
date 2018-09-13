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
				position(0.0f, 0.0f, 0.0f),
				size(1.0f, 1.0f),
				rotation(0.0f),
				dirty(true) { }


		inline explicit Transform2D(const vec3 &position, const vec2 &size, float rotationDeg = 0.0f) :
				position(position),
				size(size),
				rotation(rotationDeg),
				dirty(true) { }

		inline const std::array<vec3, 4> &getVertices() const;

		inline void set(const vec3 &position, const vec2 &size, float angleDeg = 0.0f);

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
		mutable std::array<vec3, 4> vertices;
		mutable bool dirty;

		vec3 position;
		float rotation;
		vec2 size;
	};


	void Transform2D::set(const vec3 &position, const vec2 &size, float angleDeg) {
		Transform2D::position = position;
		Transform2D::size = size;
		rotation = angleDeg;
		dirty = true;
	}

	const std::array<vec3, 4> &Transform2D::getVertices() const {
		if (dirty) {
			dirty = false;

			const float localX = -size.x / 2.0f;
			const float localY = -size.y / 2.0f;
			const float localX2 = localX + size.x;
			const float localY2 = localY + size.y;
			const float worldOriginX = position.x - localX;
			const float worldOriginY = position.y - localY;

			const float cos = cosf(to_rad(rotation));
			const float sin = sinf(to_rad(rotation));
			const float localXCos = localX * cos;
			const float localXSin = localX * sin;
			const float localYCos = localY * cos;
			const float localYSin = localY * sin;
			const float localX2Cos = localX2 * cos;
			const float localX2Sin = localX2 * sin;
			const float localY2Cos = localY2 * cos;
			const float localY2Sin = localY2 * sin;

			vertices[0] = {localXCos - localYSin + worldOriginX, localYCos + localXSin + worldOriginY, position.z};
			vertices[1] = {localXCos - localY2Sin + worldOriginX, localY2Cos + localXSin + worldOriginY, position.z};
			vertices[2] = {localX2Cos - localY2Sin + worldOriginX, localY2Cos + localX2Sin + worldOriginY, position.z};
			vertices[3] = {vertices[0].x + (vertices[2].x - vertices[1].x),
			               vertices[2].y - (vertices[1].y - vertices[0].y),
			               position.z};
		}

		return vertices;
	}


	inline void Transform2D::rotate(float angleDeg) {
		rotation += angleDeg;

		if (rotation < -360.0f) {
			rotation += 360.0f;
		} else if (rotation > 360.0f) {
			rotation -= 360.0f;
		}

		dirty = true;
	}

	inline void Transform2D::move(const vec2 &dir) {
		position.x += dir.x;
		position.y += dir.y;
		dirty = true;
	}

}


#endif //X808_TRANSFORM2D_HPP
