//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_VEC2_HPP
#define X808_VEC2_HPP


#include "common.hpp"

namespace xe {

	struct vec3;

	struct XE_API vec2 {
		float x;
		float y;

		vec2();
		vec2(float x, float y);
		vec2(const vec2 &other);
		explicit vec2(const vec3 &other);

		vec2 normalize();

		static float length(const vec2 &v);
		static float max(const vec2 &v);

		static float dot(const vec2 &v1, const vec2 &v2);
		static vec2 normalize(const vec2 &v);
		static float cross(const vec2 &v1, const vec2 &v2);
		static vec2 lerp(const vec2 &v, const vec2 &dest, float lerpFactor);
		static vec2 rotate(const vec2 &v, float angle);
	};

	//just in case
	typedef vec2 vec2;

	///----- operators -----///
	inline vec2 operator+(const vec2 &left, const vec2 &right) {
		return vec2(left.x + right.x, left.y + right.y);
	}

	inline vec2 operator-(const vec2 &left, const vec2 &right) {
		return vec2(left.x - right.x, left.y - right.y);
	}

	inline vec2 operator*(const vec2 &left, const vec2 &right) {
		return vec2(left.x * right.x, left.y * right.x);
	}

	inline vec2 operator/(const vec2 &left, const vec2 &right) {
		return vec2(left.x / right.x, left.y / right.x);
	}

	inline vec2 operator+(const vec2 &left, float right) {
		return vec2(left.x + right, left.y + right);
	}

	inline vec2 operator-(const vec2 &left, float right) {
		return vec2(left.x - right, left.y - right);
	}

	inline vec2 operator*(const vec2 &left, float right) {
		return vec2(left.x * right, left.y * right);
	}

	inline vec2 operator/(const vec2 &left, float right) {
		return vec2(left.x / right, left.y / right);
	}

	inline vec2 &operator+=(vec2 &left, const vec2 &right) {
		left.x += right.x;
		left.y += right.y;
		return left;
	}

	inline vec2 &operator-=(vec2 &left, const vec2 &right) {
		left.x -= right.x;
		left.y -= right.y;
		return left;
	}

	inline vec2 &operator*=(vec2 &left, const vec2 &right) {
		left.x *= right.x;
		left.y *= right.y;
		return left;
	}

	inline vec2 &operator/=(vec2 &left, const vec2 &right) {
		left.x /= right.x;
		left.y /= right.y;
		return left;
	}

	inline vec2 &operator+=(vec2 &left, float right) {
		left.x += right;
		left.y += right;
		return left;
	}

	inline vec2 &operator-=(vec2 &left, float right) {
		left.x -= right;
		left.y -= right;
		return left;
	}

	inline vec2 &operator*=(vec2 &left, float right) {
		left.x *= right;
		left.y *= right;
		return left;
	}

	inline vec2 &operator/=(vec2 &left, float right) {
		left.x /= right;
		left.y /= right;
		return left;
	}

	inline bool operator==(const vec2 &left, const vec2 &right) {
		return (left.x == right.x) && (left.y == right.y);
	}

	inline bool operator!=(const vec2 &left, const vec2 &right) {
		return (left.x != right.x) || (left.y != right.y);
	}

	inline bool operator<(const vec2 &left, const vec2 &right) {
		return (left.x < right.x) && (left.y < right.y);
	}

	inline bool operator<=(const vec2 &left, const vec2 &right) {
		return (left.x <= right.x) && (left.y <= right.y);
	}

	inline bool operator>(const vec2 &left, const vec2 &right) {
		return (left.x > right.x) && (left.y > right.y);
	}

	inline bool operator>=(const vec2 &left, const vec2 &right) {
		return (left.x >= right.x) && (left.y >= right.y);
	}

}


#endif //X808_VEC2_HPP
