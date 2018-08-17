//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_QUAT_HPP
#define X808_QUAT_HPP


#include <xe/common.hpp>

namespace xe {

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
		explicit quat(const vec3 &axis, float angleDeg);
		explicit quat(const vec4 &vec);
		explicit quat(float scalar);
		explicit quat(const mat4 &rot);

		vec3 getAxis() const;
		vec3 toEulerAngles() const;
		mat4 toRotationMatrix() const;

		vec3 getForward() const;
		vec3 getBackward() const;
		vec3 getUp() const;
		vec3 getDown() const;
		vec3 getRight() const;
		vec3 getLeft() const;

		static float length(const quat &q);
		static quat normalize(const quat &q);

		static float dot(const quat &left, const quat &right);
		static quat conjugate(const quat &q);
		static vec3 rotate(const quat &q, const vec3 &vec);

		static quat rotation(const vec3 &unitVec0, const vec3 &unitVec1);
		static quat rotation(float angleDeg, const vec3 &unitVec);
		static quat rotation(const vec3 &anglesDeg);
		static quat rotationX(float angleDeg);
		static quat rotationY(float angleDeg);
		static quat rotationZ(float angleDeg);
	};

	typedef quat quat;

	///----- operators -----///
	quat XE_API operator+(const quat &left, const quat &right);
	quat XE_API operator-(const quat &left, const quat &right);
	quat XE_API operator*(const quat &left, const quat &right);
	quat XE_API operator*(const quat &left, float right);
	quat XE_API operator*(const quat &left, const vec3 &right);
	quat XE_API operator/(const quat &left, float right);

	quat XE_API operator+=(quat &left, const quat &right);
	quat XE_API operator-=(quat &left, const quat &right);
	quat XE_API operator*=(quat &left, const quat &right);
	quat XE_API operator*=(quat &left, float right);
	quat XE_API operator*=(quat &left, const vec3 &right);
	quat XE_API operator/=(quat &left, float right);

}

#endif //X808_QUAT_HPP
