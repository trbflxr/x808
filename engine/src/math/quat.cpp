//
// Created by FLXR on 6/28/2018.
//

#include "quat.hpp"
#include "math.hpp"

float norm(const xe::math::quat &q) {
	float result = (q.x * q.x);
	result = (result + (q.y * q.y));
	result = (result + (q.z * q.z));
	result = (result + (q.w * q.w));
	return result;
}

float length(const xe::math::quat &q) {
	return sqrtf(norm(q));
}

xe::math::quat normalizeQuat(const xe::math::quat &q) {
	const float lenSqr = norm(q);
	const float lenInv = 1.0f / sqrtf(lenSqr);
	return q * lenInv;
}

xe::math::quat normalizeEst(const xe::math::quat &q) {
	const float lenSqr = norm(q);
	const float lenInv = 1.0f / sqrtf(lenSqr);
	return q * lenInv;
}


xe::math::quat::quat() : x(0), y(0), z(0), w(1) { }
xe::math::quat::quat(const xe::quat &q) : x(q.x), y(q.y), z(q.z), w(q.w) { }
xe::math::quat::quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
xe::math::quat::quat(const vec3 &xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
xe::math::quat::quat(const vec4 &vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) { }
xe::math::quat::quat(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar) { }

xe::vec3 xe::math::quat::getAxis() const {
	float x = 1.0f - w * w;
	if (x < 0.0000001f) return XAXIS;

	float x2 = x * x;
	return vec3(x, y, z) / x2;
}

xe::vec3 xe::math::quat::toEulerAngles() const {
	return vec3(atan2f(2 * x * w - 2 * y * z, 1 - 2 * x * x - 2 * z * z),
	            atan2f(2 * y * w - 2 * x * z, 1 - 2 * y * y - 2 * z * z),
	            asinf(2 * x * y + 2 * z * w));
}

float xe::math::dot(const quat &left, const quat &right) {
	float result = (left.x * right.x);
	result = (result + (left.y * right.y));
	result = (result + (left.z * right.z));
	result = (result + (left.w * right.w));
	return result;
}

xe::math::quat xe::math::conjugate(const quat &q) {
	return quat(-q.x, -q.y, -q.z, q.w);
}

xe::math::vec3 xe::math::rotate(const quat &q, const vec3 &vec) {
	const float tmpX = (((q.w * vec.x) + (q.y * vec.z)) - (q.z * vec.y));
	const float tmpY = (((q.w * vec.y) + (q.z * vec.x)) - (q.x * vec.z));
	const float tmpZ = (((q.w * vec.z) + (q.x * vec.y)) - (q.y * vec.x));
	const float tmpW = (((q.x * vec.x) + (q.y * vec.y)) + (q.z * vec.z));

	return vec3(((((tmpW * q.x) + (tmpX * q.w)) - (tmpY * q.z)) + (tmpZ * q.y)),
	            ((((tmpW * q.y) + (tmpY * q.w)) - (tmpZ * q.x)) + (tmpX * q.z)),
	            ((((tmpW * q.z) + (tmpZ * q.w)) - (tmpX * q.y)) + (tmpY * q.x)));
}

xe::math::quat xe::math::fromEulerAngles(const vec3 &angles) {
	quat pitch(XAXIS, angles.x);
	quat yaw(YAXIS, angles.y);
	quat roll(ZAXIS, angles.z);
	return pitch * yaw * roll;
}

xe::math::quat xe::math::rotation(const vec3 &unitVec0, const vec3 &unitVec1) {
	const float cosHalfAngleX2 = sqrtf((2.0f * (1.0f + dot(unitVec0, unitVec1))));
	const float recipCosHalfAngleX2 = (1.0f / cosHalfAngleX2);
	return quat((cross(unitVec0, unitVec1) * recipCosHalfAngleX2), (cosHalfAngleX2 * 0.5f));
}

xe::math::quat xe::math::rotation(float radians, const vec3 &unitVec) {
	const float angle = radians * 0.5f;
	return quat((unitVec * sinf(angle)), cosf(angle));
}

xe::math::quat xe::math::rotationX(float radians) {
	const float angle = radians * 0.5f;
	return quat(sinf(angle), 0.0f, 0.0f, cosf(angle));
}

xe::math::quat xe::math::rotationY(float radians) {
	const float angle = radians * 0.5f;
	return quat(0.0f, sinf(angle), 0.0f, cosf(angle));
}

xe::math::quat xe::math::rotationZ(float radians) {
	const float angle = radians * 0.5f;
	return quat(0.0f, 0.0f, sinf(angle), cosf(angle));
}


///operators
xe::math::quat xe::math::operator+(const quat &left, const quat &right) {
	return quat(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}

xe::math::quat xe::math::operator-(const quat &left, const quat &right) {
	return quat(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}

xe::math::quat xe::math::operator*(const quat &left, const quat &right) {
	return normalizeQuat(quat((((left.w * right.x) + (left.x * right.w)) + (left.y * right.z)) - (left.z * right.y),
	                          (((left.w * right.y) + (left.y * right.w)) + (left.z * right.x)) - (left.x * right.z),
	                          (((left.w * right.z) + (left.z * right.w)) + (left.x * right.y)) - (left.y * right.x),
	                          (((left.w * right.w) - (left.x * right.x)) - (left.y * right.y)) - (left.z * right.z)));
}

xe::math::quat xe::math::operator*(const quat &left, float right) {
	return quat(left.x * right, left.y * right, left.z * right, left.w * right);
}

xe::math::quat xe::math::operator/(const quat &left, float right) {
	return quat(left.x / right, left.y / right, left.z / right, left.w / right);
}

xe::math::quat xe::math::operator+=(quat &left, const quat &right) {
	left = left + right;
	return left;
}

xe::math::quat xe::math::operator-=(quat &left, const quat &right) {
	left = left - right;
	return left;
}

xe::math::quat xe::math::operator*=(quat &left, const quat &right) {
	left = left * right;
	return left;
}

xe::math::quat xe::math::operator*=(quat &left, float right) {
	left = left * right;
	return left;
}

xe::math::quat xe::math::operator/=(quat &left, float right) {
	left = left / right;
	return left;
}

