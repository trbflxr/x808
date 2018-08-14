//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_VEC4_HPP
#define X808_VEC4_HPP


#include "common.hpp"

namespace xe {

	struct vec3;
	struct mat4;

	struct XE_API vec4 {
		float x;
		float y;
		float z;
		float w;

		vec4();
		explicit vec4(float scalar);
		vec4(float x, float y, float z, float w);
		explicit vec4(const vec3 &xyz, float w);
		vec4(const vec4 &vec);

		static float dot(const vec4 &v1, const vec4 &v2);

		static vec4 transform(const vec4 &vec, const mat4 &m);
	};

	typedef vec4 vec4;


	///----- operators -----///
	vec4 XE_API operator*(const vec4 &left, const mat4 &right);

	inline vec4 operator+(const vec4 &left, const vec4 &right) {
		return vec4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
	}

	inline vec4 operator-(const vec4 &left, const vec4 &right) {
		return vec4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
	}

	inline vec4 operator*(const vec4 &left, const vec4 &right) {
		return vec4(left.x * right.x, left.y * right.x, left.z * right.z, left.w * right.w);
	}

	inline vec4 operator/(const vec4 &left, const vec4 &right) {
		return vec4(left.x / right.x, left.y / right.x, left.z / right.z, left.w / right.w);
	}

	inline vec4 operator+(const vec4 &left, float right) {
		return vec4(left.x + right, left.y + right, left.z + right, left.w + right);
	}

	inline vec4 operator-(const vec4 &left, float right) {
		return vec4(left.x - right, left.y - right, left.z - right, left.w - right);
	}

	inline vec4 operator*(const vec4 &left, float right) {
		return vec4(left.x * right, left.y * right, left.z * right, left.w * right);
	}

	inline vec4 operator/(const vec4 &left, float right) {
		return vec4(left.x / right, left.y / right, left.z / right, left.w / right);
	}

	inline bool operator==(const vec4 &left, const vec4 &right) {
		return (left.x == right.x) && (left.y == right.y) && (left.z == right.z) && (left.w == right.w);
	}

	inline bool operator!=(const vec4 &left, const vec4 &right) {
		return (left.x != right.x) || (left.y != right.y) || (left.z != right.z) || (left.w != right.w);
	}

	inline vec4 &operator+=(vec4 &left, const vec4 &right) {
		left.x += right.x;
		left.y += right.y;
		left.z += right.z;
		left.w += right.w;
		return left;
	}

	inline vec4 &operator-=(vec4 &left, const vec4 &right) {
		left.x -= right.x;
		left.y -= right.y;
		left.z -= right.z;
		left.w -= right.w;
		return left;
	}

	inline vec4 &operator*=(vec4 &left, const vec4 &right) {
		left.x *= right.x;
		left.y *= right.y;
		left.z *= right.z;
		left.w *= right.w;
		return left;
	}

	inline vec4 &operator/=(vec4 &left, const vec4 &right) {
		left.x /= right.x;
		left.y /= right.y;
		left.z /= right.z;
		left.w /= right.w;
		return left;
	}

	inline vec4 &operator+=(vec4 &left, float right) {
		left.x += right;
		left.y += right;
		left.z += right;
		left.w += right;
		return left;
	}

	inline vec4 &operator-=(vec4 &left, float right) {
		left.x -= right;
		left.y -= right;
		left.z -= right;
		left.w -= right;
		return left;
	}

	inline vec4 &operator*=(vec4 &left, float right) {
		left.x *= right;
		left.y *= right;
		left.z *= right;
		left.w *= right;
		return left;
	}

	inline vec4 &operator/=(vec4 &left, float right) {
		left.x /= right;
		left.y /= right;
		left.z /= right;
		left.w /= right;
		return left;
	}

	inline bool operator<(const vec4 &left, const vec4 &right) {
		return (left.x < right.x) && (left.y < right.y) && (left.z < right.z) && (left.w < right.w);
	}

	inline bool operator<=(const vec4 &left, const vec4 &right) {
		return (left.x <= right.x) && (left.y <= right.y) && (left.z <= right.z) && (left.w <= right.w);
	}

	inline bool operator>(const vec4 &left, const vec4 &right) {
		return (left.x > right.x) && (left.y > right.y) && (left.z > right.z) && (left.w > right.w);
	}

	inline bool operator>=(const vec4 &left, const vec4 &right) {
		return (left.x >= right.x) && (left.y >= right.y) && (left.z >= right.z) && (left.w >= right.w);
	}

}


#endif //X808_VEC4_HPP
