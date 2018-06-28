//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_VEC3_HPP
#define X808_VEC3_HPP


#include "common.hpp"

namespace xe {
	namespace math {

		struct vec2;
		struct vec4;
		struct mat4;

		struct XE_API vec3 {
			float x;
			float y;
			float z;

			vec3();
			vec3(float x, float y, float z);
			explicit vec3(float x, float y);
			vec3(const vec3 &other);
			explicit vec3(const vec2 &other);
			explicit vec3(const vec4 &other);
		};

		XE_API float length(const vec3 &v);
		XE_API float max(const vec3 &v);

		XE_API float dot(const vec3 &v1, const vec3 &v2);
		XE_API vec3 cross(const vec3 &v1, const vec3 &v2);
		XE_API vec3 normalize(const vec3 &v);
		XE_API vec3 rotate(const vec3 &v, const vec3 &axis, float angle);
		XE_API vec3 lerp(const vec3 &v, const vec3 &dest, float lerpFactor);

		XE_API vec3 operator+(const vec3 &left, const vec3 &right);
		XE_API vec3 operator-(const vec3 &left, const vec3 &right);
		XE_API vec3 operator*(const vec3 &left, const vec3 &right);
		XE_API vec3 operator/(const vec3 &left, const vec3 &right);

		XE_API vec3 operator+(const vec3 &left, float right);
		XE_API vec3 operator-(const vec3 &left, float right);
		XE_API vec3 operator*(const vec3 &left, float right);
		XE_API vec3 operator/(const vec3 &left, float right);

		XE_API bool operator==(const vec3 &left, const vec3 &right);
		XE_API bool operator!=(const vec3 &left, const vec3 &right);

		XE_API vec3 &operator+=(vec3 &left, const vec3 &right);
		XE_API vec3 &operator-=(vec3 &left, const vec3 &right);
		XE_API vec3 &operator*=(vec3 &left, const vec3 &right);
		XE_API vec3 &operator/=(vec3 &left, const vec3 &right);

		XE_API vec3 &operator+=(vec3 &left, float right);
		XE_API vec3 &operator-=(vec3 &left, float right);
		XE_API vec3 &operator*=(vec3 &left, float right);
		XE_API vec3 &operator/=(vec3 &left, float right);

		XE_API bool operator<(const vec3 &left, const vec3 &right);
		XE_API bool operator<=(const vec3 &left, const vec3 &right);
		XE_API bool operator>(const vec3 &left, const vec3 &right);
		XE_API bool operator>=(const vec3 &left, const vec3 &right);

#define XAXIS vec3(1.0f, 0.0f, 0.0f)
#define YAXIS vec3(0.0f, 1.0f, 0.0f)
#define ZAXIS vec3(0.0f, 0.0f, 1.0f)

	}

	typedef math::vec3 vec3;
}

#endif //X808_VEC3_HPP
