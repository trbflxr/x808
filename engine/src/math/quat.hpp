//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_QUAT_HPP
#define X808_QUAT_HPP


#include "common.hpp"

namespace xe {
	namespace math {

		struct vec3;
		struct vec4;
		struct mat4;

		struct XE_API quat {
			float x;
			float y;
			float z;
			float w;

			quat();
			quat(const quat &q);
			explicit quat(float x, float y, float z, float w);
			explicit quat(const vec3 &xyz, float w);
			explicit quat(const vec4 &vec);
			explicit quat(float scalar);
			explicit quat(const mat4 &rot);

			vec3 getAxis() const;
			vec3 toEulerAngles() const;
			mat4 toRotationMatrix() const;
		};

		XE_API float length(const quat &q);
		XE_API quat normalize(const quat &q);

		XE_API float dot(const quat &left, const quat &right);
		XE_API quat conjugate(const quat &q);
		XE_API vec3 rotate(const quat &q, const vec3 &vec);

		XE_API quat fromEulerAngles(const vec3 &angles);
		XE_API quat rotation(const vec3 &unitVec0, const vec3 &unitVec1);
		XE_API quat rotation(float radians, const vec3 &unitVec);
		XE_API quat rotationX(float radians);
		XE_API quat rotationY(float radians);
		XE_API quat rotationZ(float radians);

		XE_API quat operator+(const quat &left, const quat &right);
		XE_API quat operator-(const quat &left, const quat &right);
		XE_API quat operator*(const quat &left, const quat &right);
		XE_API quat operator*(const quat &left, float right);
		XE_API quat operator/(const quat &left, float right);

		XE_API quat operator+=(quat &left, const quat &right);
		XE_API quat operator-=(quat &left, const quat &right);
		XE_API quat operator*=(quat &left, const quat &right);
		XE_API quat operator*=(quat &left, float right);
		XE_API quat operator/=(quat &left, float right);
	}

	typedef math::quat quat;
}

#endif //X808_QUAT_HPP
