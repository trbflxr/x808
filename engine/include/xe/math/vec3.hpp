//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_VEC3_HPP
#define X808_VEC3_HPP


#include <xe/common.hpp>

namespace xe {

	struct vec2;
	struct vec4;
	struct quat;
	struct mat4;

	struct XE_API vec3 {
		float x;
		float y;
		float z;

		vec3();
		explicit vec3(float val);
		vec3(float x, float y, float z);
		explicit vec3(float x, float y);
		vec3(const vec3 &other);
		explicit vec3(const vec2 &other);
		explicit vec3(const vec4 &other);

		vec3 rotate(const quat &rotation) const;

		static float length(const vec3 &v);
		static float max(const vec3 &v);

		static float dot(const vec3 &v1, const vec3 &v2);
		static vec3 cross(const vec3 &v1, const vec3 &v2);
		static vec3 normalize(const vec3 &v);
		static vec3 rotate(const vec3 &v, const vec3 &axis, float angle);
		static vec3 lerp(const vec3 &v, const vec3 &dest, float lerpFactor);

		static vec3 transformPerspective(const vec3 &vec, const mat4 &mat);

		static const vec3 XAXIS;
		static const vec3 YAXIS;
		static const vec3 ZAXIS;
	};

	typedef vec3 vec3;


	///----- operators -----///
	vec3 XE_API operator*(const vec3 &left, const mat4 &right);

	inline vec3 operator-(const vec3 &vec) {
		return vec3(-vec.x, -vec.y, -vec.z);
	}

	inline vec3 operator+(const vec3 &left, const vec3 &right) {
		return vec3(left.x + right.x, left.y + right.y, left.z + right.z);
	}

	inline vec3 operator-(const vec3 &left, const vec3 &right) {
		return vec3(left.x - right.x, left.y - right.y, left.z - right.z);
	}

	inline vec3 operator*(const vec3 &left, const vec3 &right) {
		return vec3(left.x * right.x, left.y * right.x, left.z * right.z);
	}

	inline vec3 operator/(const vec3 &left, const vec3 &right) {
		return vec3(left.x / right.x, left.y / right.x, left.z / right.z);
	}

	inline vec3 operator+(const vec3 &left, float right) {
		return vec3(left.x + right, left.y + right, left.z + right);
	}

	inline vec3 operator-(const vec3 &left, float right) {
		return vec3(left.x - right, left.y - right, left.z - right);
	}

	inline vec3 operator*(const vec3 &left, float right) {
		return vec3(left.x * right, left.y * right, left.z * right);
	}

	inline vec3 operator/(const vec3 &left, float right) {
		return vec3(left.x / right, left.y / right, left.z / right);
	}

	inline bool operator==(const vec3 &left, const vec3 &right) {
		return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
	}

	inline bool operator!=(const vec3 &left, const vec3 &right) {
		return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
	}

	inline vec3 &operator+=(vec3 &left, const vec3 &right) {
		left.x += right.x;
		left.y += right.y;
		left.z += right.z;
		return left;
	}

	inline vec3 &operator-=(vec3 &left, const vec3 &right) {
		left.x -= right.x;
		left.y -= right.y;
		left.z -= right.z;
		return left;
	}

	inline vec3 &operator*=(vec3 &left, const vec3 &right) {
		left.x *= right.x;
		left.y *= right.y;
		left.z *= right.z;
		return left;
	}

	inline vec3 &operator/=(vec3 &left, const vec3 &right) {
		left.x /= right.x;
		left.y /= right.y;
		left.z /= right.z;
		return left;
	}

	inline vec3 &operator+=(vec3 &left, float right) {
		left.x += right;
		left.y += right;
		left.z += right;
		return left;
	}

	inline vec3 &operator-=(vec3 &left, float right) {
		left.x -= right;
		left.y -= right;
		left.z -= right;
		return left;
	}

	inline vec3 &operator*=(vec3 &left, float right) {
		left.x *= right;
		left.y *= right;
		left.z *= right;
		return left;
	}

	inline vec3 &operator/=(vec3 &left, float right) {
		left.x /= right;
		left.y /= right;
		left.z /= right;
		return left;
	}

	inline bool operator<(const vec3 &left, const vec3 &right) {
		return (left.x < right.x) && (left.y < right.y) && (left.z < right.z);
	}

	inline bool operator<=(const vec3 &left, const vec3 &right) {
		return (left.x <= right.x) && (left.y <= right.y) && (left.z <= right.z);
	}

	inline bool operator>(const vec3 &left, const vec3 &right) {
		return (left.x > right.x) && (left.y > right.y) && (left.z > right.z);
	}

	inline bool operator>=(const vec3 &left, const vec3 &right) {
		return (left.x >= right.x) && (left.y >= right.y) && (left.z >= right.z);
	}

}

#endif //X808_VEC3_HPP
