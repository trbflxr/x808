//
// Created by FLXR on 6/28/2018.
//

#include "vec4.hpp"
#include "math.hpp"

xe::math::vec4::vec4() : x(0), y(0), z(0), w(0) { }
xe::math::vec4::vec4(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar) { }
xe::math::vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
xe::math::vec4::vec4(const vec3 &xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
xe::math::vec4::vec4(const vec4 &vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) { }

float xe::math::dot(const vec4 &v1, const vec4 &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

xe::math::vec4 xe::math::operator+(const vec4 &left, const vec4 &right) {
	return vec4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}

xe::math::vec4 xe::math::operator-(const vec4 &left, const vec4 &right) {
	return vec4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}

xe::math::vec4 xe::math::operator*(const vec4 &left, const vec4 &right) {
	return vec4(left.x * right.x, left.y * right.x, left.z * right.z, left.w * right.w);
}

xe::math::vec4 xe::math::operator/(const vec4 &left, const vec4 &right) {
	return vec4(left.x / right.x, left.y / right.x, left.z / right.z, left.w / right.w);
}

xe::math::vec4 xe::math::operator+(const vec4 &left, float right) {
	return vec4(left.x + right, left.y + right, left.z + right, left.w + right);
}

xe::math::vec4 xe::math::operator-(const vec4 &left, float right) {
	return vec4(left.x - right, left.y - right, left.z - right, left.w - right);
}

xe::math::vec4 xe::math::operator*(const vec4 &left, float right) {
	return vec4(left.x * right, left.y * right, left.z * right, left.w * right);
}

xe::math::vec4 xe::math::operator/(const vec4 &left, float right) {
	return vec4(left.x / right, left.y / right, left.z / right, left.w / right);
}

bool xe::math::operator==(const vec4 &left, const vec4 &right) {
	return (left.x == right.x) && (left.y == right.y) && (left.z == right.z) && (left.w == right.w);
}

bool xe::math::operator!=(const vec4 &left, const vec4 &right) {
	return (left.x != right.x) || (left.y != right.y) || (left.z != right.z) || (left.w != right.w);
}

xe::math::vec4 &xe::math::operator+=(vec4 &left, const vec4 &right) {
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	left.w += right.w;
	return left;
}

xe::math::vec4 &xe::math::operator-=(vec4 &left, const vec4 &right) {
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	left.w -= right.w;
	return left;
}

xe::math::vec4 &xe::math::operator*=(vec4 &left, const vec4 &right) {
	left.x *= right.x;
	left.y *= right.y;
	left.z *= right.z;
	left.w *= right.w;
	return left;
}

xe::math::vec4 &xe::math::operator/=(vec4 &left, const vec4 &right) {
	left.x /= right.x;
	left.y /= right.y;
	left.z /= right.z;
	left.w /= right.w;
	return left;
}

xe::math::vec4 &xe::math::operator+=(vec4 &left, float right) {
	left.x += right;
	left.y += right;
	left.z += right;
	left.w += right;
	return left;
}

xe::math::vec4 &xe::math::operator-=(vec4 &left, float right) {
	left.x -= right;
	left.y -= right;
	left.z -= right;
	left.w -= right;
	return left;
}

xe::math::vec4 &xe::math::operator*=(vec4 &left, float right) {
	left.x *= right;
	left.y *= right;
	left.z *= right;
	left.w *= right;
	return left;
}

xe::math::vec4 &xe::math::operator/=(vec4 &left, float right) {
	left.x /= right;
	left.y /= right;
	left.z /= right;
	left.w /= right;
	return left;
}

bool xe::math::operator<(const vec4 &left, const vec4 &right) {
	return (left.x < right.x) && (left.y < right.y) && (left.z < right.z) && (left.w < right.w);
}

bool xe::math::operator<=(const vec4 &left, const vec4 &right) {
	return (left.x <= right.x) && (left.y <= right.y) && (left.z <= right.z) && (left.w <= right.w);
}

bool xe::math::operator>(const vec4 &left, const vec4 &right) {
	return (left.x > right.x) && (left.y > right.y) && (left.z > right.z) && (left.w > right.w);
}

bool xe::math::operator>=(const vec4 &left, const vec4 &right) {
	return (left.x >= right.x) && (left.y >= right.y) && (left.z >= right.z) && (left.w >= right.w);
}
