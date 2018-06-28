//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_VEC2_HPP
#define X808_VEC2_HPP


#include "common.hpp"

namespace xe {
	namespace math {

		struct vec3;

		struct XE_API vec2 {
			float x;
			float y;

			vec2();
			vec2(float x, float y);
			vec2(const vec2 &other);
			explicit vec2(const vec3 &other);
		};

		XE_API float length(const vec2 &v);
		XE_API float max(const vec2 &v);

		XE_API float dot(const vec2 &v1, const vec2 &v2);
		XE_API vec2 normalize(const vec2 &v);
		XE_API float cross(const vec2 &v1, const vec2 &v2);
		XE_API vec2 lerp(const vec2 &v, const vec2 &dest, float lerpFactor);
		XE_API vec2 rotate(const vec2 &v, float angle);

		XE_API vec2 operator+(const vec2 &left, const vec2 &right);
		XE_API vec2 operator-(const vec2 &left, const vec2 &right);
		XE_API vec2 operator*(const vec2 &left, const vec2 &right);
		XE_API vec2 operator/(const vec2 &left, const vec2 &right);

		XE_API vec2 operator+(const vec2 &left, float right);
		XE_API vec2 operator-(const vec2 &left, float right);
		XE_API vec2 operator*(const vec2 &left, float right);
		XE_API vec2 operator/(const vec2 &left, float right);

		XE_API bool operator==(const vec2 &left, const vec2 &right);
		XE_API bool operator!=(const vec2 &left, const vec2 &right);

		XE_API vec2 &operator+=(vec2 &left, const vec2 &right);
		XE_API vec2 &operator-=(vec2 &left, const vec2 &right);
		XE_API vec2 &operator*=(vec2 &left, const vec2 &right);
		XE_API vec2 &operator/=(vec2 &left, const vec2 &right);

		XE_API vec2 &operator+=(vec2 &left, float right);
		XE_API vec2 &operator-=(vec2 &left, float right);
		XE_API vec2 &operator*=(vec2 &left, float right);
		XE_API vec2 &operator/=(vec2 &left, float right);

		XE_API bool operator<(const vec2 &left, const vec2 &right);
		XE_API bool operator<=(const vec2 &left, const vec2 &right);
		XE_API bool operator>(const vec2 &left, const vec2 &right);
		XE_API bool operator>=(const vec2 &left, const vec2 &right);


	}

	typedef math::vec2 vec2;
}


#endif //X808_VEC2_HPP
