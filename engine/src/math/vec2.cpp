//
// Created by FLXR on 6/28/2018.
//

#include "vec2.hpp"
#include "math.hpp"

xe::math::vec2::vec2() : x(0), y(0) { }
xe::math::vec2::vec2(float x, float y) : x(x), y(y) { }
xe::math::vec2::vec2(const vec2 &other) : x(other.x), y(other.y) { }
xe::math::vec2::vec2(const vec3 &other) : x(other.x), y(other.y) { }

float xe::math::length(const vec2 &v){
	return sqrtf(v.x * v.x + v.y * v.y);
}

float xe::math::max(const vec2 &v){
	return v.x > v.y ? v.x : v.y;
}

float xe::math::dot(const vec2 &v1, const vec2 &v2){
	return v1.x * v2.x + v1.y * v2.y;
}

xe::math::vec2 xe::math::normalize(const vec2 &v){
	const float l = length(v);
	return vec2(v.x / l, v.y / l);
}

float xe::math::cross(const vec2 &v1, const vec2 &v2){
	return v1.x * v2.y - v1.y * v2.x;
}

xe::math::vec2 xe::math::lerp(const vec2 &v, const vec2 &dest, float lerpFactor){
	return (dest - v) * lerpFactor + v;
}

xe::math::vec2 xe::math::rotate(const vec2 &v, float angle){
	const float rad = to_rad(angle);
	const float cos = cosf(rad);
	const float sin = sinf(rad);

	return vec2(v.x * cos - v.y * sin, v.x * sin + v.y * cos);
}

xe::math::vec2 xe::math::operator+(const vec2 &left, const vec2 &right) {
	return vec2(left.x + right.x, left.y + right.y);
}

xe::math::vec2 xe::math::operator-(const vec2 &left, const vec2 &right) {
	return vec2(left.x - right.x, left.y - right.y);
}

xe::math::vec2 xe::math::operator*(const vec2 &left, const vec2 &right) {
	return vec2(left.x * right.x, left.y * right.x);
}

xe::math::vec2 xe::math::operator/(const vec2 &left, const vec2 &right) {
	return vec2(left.x / right.x, left.y / right.x);
}

xe::math::vec2 xe::math::operator+(const vec2 &left, float right) {
	return vec2(left.x + right, left.y + right);
}

xe::math::vec2 xe::math::operator-(const vec2 &left, float right) {
	return vec2(left.x - right, left.y - right);
}

xe::math::vec2 xe::math::operator*(const vec2 &left, float right) {
	return vec2(left.x * right, left.y * right);
}

xe::math::vec2 xe::math::operator/(const vec2 &left, float right) {
	return vec2(left.x / right, left.y / right);
}

bool xe::math::operator==(const vec2 &left, const vec2 &right) {
	return (left.x == right.x) && (left.y == right.y);
}

bool xe::math::operator!=(const vec2 &left, const vec2 &right) {
	return (left.x != right.x) || (left.y != right.y);
}

xe::math::vec2 &xe::math::operator+=(vec2 &left, const vec2 &right) {
	left.x += right.x;
	left.y += right.y;
	return left;
}

xe::math::vec2 &xe::math::operator-=(vec2 &left, const vec2 &right) {
	left.x -= right.x;
	left.y -= right.y;
	return left;
}

xe::math::vec2 &xe::math::operator*=(vec2 &left, const vec2 &right) {
	left.x *= right.x;
	left.y *= right.y;
	return left;
}

xe::math::vec2 &xe::math::operator/=(vec2 &left, const vec2 &right) {
	left.x /= right.x;
	left.y /= right.y;
	return left;
}

xe::math::vec2 &xe::math::operator+=(vec2 &left, float right) {
	left.x += right;
	left.y += right;
	return left;
}

xe::math::vec2 &xe::math::operator-=(vec2 &left, float right) {
	left.x -= right;
	left.y -= right;
	return left;
}

xe::math::vec2 &xe::math::operator*=(vec2 &left, float right) {
	left.x *= right;
	left.y *= right;
	return left;
}

xe::math::vec2 &xe::math::operator/=(vec2 &left, float right) {
	left.x /= right;
	left.y /= right;
	return left;
}

bool xe::math::operator<(const vec2 &left, const vec2 &right) {
	return (left.x < right.x) && (left.y < right.y);
}

bool xe::math::operator<=(const vec2 &left, const vec2 &right) {
	return (left.x <= right.x) && (left.y <= right.y);
}

bool xe::math::operator>(const vec2 &left, const vec2 &right) {
	return (left.x > right.x) && (left.y > right.y);
}

bool xe::math::operator>=(const vec2 &left, const vec2 &right) {
	return (left.x >= right.x) && (left.y >= right.y);
}
