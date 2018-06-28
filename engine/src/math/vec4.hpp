//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_VEC4_HPP
#define X808_VEC4_HPP


#include "common.hpp"

namespace xe {
	namespace math {

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
		};

		XE_API float dot(const vec4 &v1, const vec4 &v2);

		XE_API vec4 operator+(const vec4 &left, const vec4 &right);
		XE_API vec4 operator-(const vec4 &left, const vec4 &right);
		XE_API vec4 operator*(const vec4 &left, const vec4 &right);
		XE_API vec4 operator/(const vec4 &left, const vec4 &right);

		XE_API vec4 operator+(const vec4 &left, float right);
		XE_API vec4 operator-(const vec4 &left, float right);
		XE_API vec4 operator*(const vec4 &left, float right);
		XE_API vec4 operator/(const vec4 &left, float right);

		XE_API bool operator==(const vec4 &left, const vec4 &right);
		XE_API bool operator!=(const vec4 &left, const vec4 &right);

		XE_API vec4 &operator+=(vec4 &left, const vec4 &right);
		XE_API vec4 &operator-=(vec4 &left, const vec4 &right);
		XE_API vec4 &operator*=(vec4 &left, const vec4 &right);
		XE_API vec4 &operator/=(vec4 &left, const vec4 &right);

		XE_API vec4 &operator+=(vec4 &left, float right);
		XE_API vec4 &operator-=(vec4 &left, float right);
		XE_API vec4 &operator*=(vec4 &left, float right);
		XE_API vec4 &operator/=(vec4 &left, float right);

		XE_API bool operator<(const vec4 &left, const vec4 &right);
		XE_API bool operator<=(const vec4 &left, const vec4 &right);
		XE_API bool operator>(const vec4 &left, const vec4 &right);
		XE_API bool operator>=(const vec4 &left, const vec4 &right);

	}
	typedef math::vec4 vec4;
}


#endif //X808_VEC4_HPP
