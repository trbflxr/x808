//
// Created by FLXR on 6/28/2018.
//

#include "vec3.hpp"
#include "math.hpp"

xe::math::vec3::vec3() : x(0), y(0), z(0) { }
xe::math::vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) { }
xe::math::vec3::vec3(float x, float y) : x(x), y(y), z(0) { }
xe::math::vec3::vec3(const vec3 &vec) : x(vec.x), y(vec.y), z(vec.z) { }
xe::math::vec3::vec3(const vec2 &vec) : x(vec.x), y(vec.y), z(0.0f) { }
xe::math::vec3::vec3(const vec4 &vec) : x(vec.x), y(vec.y), z(vec.z) { }

float xe::math::length(const vec3 &v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float xe::math::max(const vec3 &v) {
	__max(v.x, __max(v.y, v.z));
}

float xe::math::dot(const vec3 &v1, const vec3 &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

xe::math::vec3 xe::math::cross(const vec3 &v1, const vec3 &v2) {
	const float x = v1.y * v2.z - v1.z * v2.y;
	const float y = v1.z * v2.x - v1.x * v2.z;
	const float z = v1.x * v2.y - v1.y * v2.x;

	return vec3(x, y, z);
}

xe::math::vec3 xe::math::normalize(const vec3 &v) {
	const float l = length(v);

	return vec3(v.x / l, v.y / l, v.z / l);
}

xe::math::vec3 xe::math::rotate(const vec3 &v, const vec3 &axis, float angle) {
	const float sin = sinf(-angle);
	const float cos = cosf(-angle);

	return cross(v, axis * sin) + v * cos + axis * dot(v, axis * (1.0f - cos));
}

xe::math::vec3 xe::math::lerp(const vec3 &v, const vec3 &dest, float lerpFactor) {
	return (dest - v) * lerpFactor + v;
}


xe::math::vec3 xe::math::operator+(const vec3 &left, const vec3 &right) {
	return vec3(left.x + right.x, left.y + right.y, left.z + right.z);
}

xe::math::vec3 xe::math::operator-(const vec3 &left, const vec3 &right) {
	return vec3(left.x - right.x, left.y - right.y, left.z - right.z);
}

xe::math::vec3 xe::math::operator*(const vec3 &left, const vec3 &right) {
	return vec3(left.x * right.x, left.y * right.x, left.z * right.z);
}

xe::math::vec3 xe::math::operator/(const vec3 &left, const vec3 &right) {
	return vec3(left.x / right.x, left.y / right.x, left.z / right.z);
}

xe::math::vec3 xe::math::operator+(const vec3 &left, float right) {
	return vec3(left.x + right, left.y + right, left.z + right);
}

xe::math::vec3 xe::math::operator-(const vec3 &left, float right) {
	return vec3(left.x - right, left.y - right, left.z - right);
}

xe::math::vec3 xe::math::operator*(const vec3 &left, float right) {
	return vec3(left.x * right, left.y * right, left.z * right);
}

xe::math::vec3 xe::math::operator/(const vec3 &left, float right) {
	return vec3(left.x / right, left.y / right, left.z / right);
}

bool xe::math::operator==(const vec3 &left, const vec3 &right) {
	return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

bool xe::math::operator!=(const vec3 &left, const vec3 &right) {
	return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}

xe::math::vec3 &xe::math::operator+=(vec3 &left, const vec3 &right) {
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	return left;
}

xe::math::vec3 &xe::math::operator-=(vec3 &left, const vec3 &right) {
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	return left;
}

xe::math::vec3 &xe::math::operator*=(vec3 &left, const vec3 &right) {
	left.x *= right.x;
	left.y *= right.y;
	left.z *= right.z;
	return left;
}

xe::math::vec3 &xe::math::operator/=(vec3 &left, const vec3 &right) {
	left.x /= right.x;
	left.y /= right.y;
	left.z /= right.z;
	return left;
}

xe::math::vec3 &xe::math::operator+=(vec3 &left, float right) {
	left.x += right;
	left.y += right;
	left.z += right;
	return left;
}

xe::math::vec3 &xe::math::operator-=(vec3 &left, float right) {
	left.x -= right;
	left.y -= right;
	left.z -= right;
	return left;
}

xe::math::vec3 &xe::math::operator*=(vec3 &left, float right) {
	left.x *= right;
	left.y *= right;
	left.z *= right;
	return left;
}

xe::math::vec3 &xe::math::operator/=(vec3 &left, float right) {
	left.x /= right;
	left.y /= right;
	left.z /= right;
	return left;
}

bool xe::math::operator<(const vec3 &left, const vec3 &right) {
	return (left.x < right.x) && (left.y < right.y) && (left.z < right.z);
}

bool xe::math::operator<=(const vec3 &left, const vec3 &right) {
	return (left.x <= right.x) && (left.y <= right.y) && (left.z <= right.z);
}

bool xe::math::operator>(const vec3 &left, const vec3 &right) {
	return (left.x > right.x) && (left.y > right.y) && (left.z > right.z);
}

bool xe::math::operator>=(const vec3 &left, const vec3 &right) {
	return (left.x >= right.x) && (left.y >= right.y) && (left.z >= right.z);
}

xe::math::vec3 xe::math::operator*(const vec3 &left, const mat4 &right) {
	return vec3(right.rows[0].x * left.x + right.rows[0].y * left.y + right.rows[0].z * left.z + right.rows[0].w,
	            right.rows[1].x * left.x + right.rows[1].y * left.y + right.rows[1].z * left.z + right.rows[1].w,
	            right.rows[2].x * left.x + right.rows[2].y * left.y + right.rows[2].z * left.z + right.rows[2].w);
}