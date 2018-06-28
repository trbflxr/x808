//
// Created by FLXR on 6/28/2018.
//

#include "aabb.hpp"
#include "math.hpp"

xe::math::aabb::aabb() : min(vec3()), max(vec3()) { }
xe::math::aabb::aabb(const xe::math::rect &rect) : min(rect.getMinBound()), max(rect.getMaxBound()) { }
xe::math::aabb::aabb(const xe::vec2 &min, const xe::vec2 &max) : min(min), max(max) { }
xe::math::aabb::aabb(const xe::vec3 &min, const xe::vec3 &max) : min(min), max(max) { }
xe::math::aabb::aabb(float x, float y, float width, float height) : min({x, y, 0.0f}), max({width, height, 0.0f}) { }
xe::math::aabb::aabb(float x, float y, float z, float w, float h, float depth) : min({x, y, z}), max({w, h, depth}) { }

bool xe::math::aabb::intersects(const xe::aabb &other) const {
	return (max > other.min && min < other.max) || (min > other.max && max < other.min);
}

bool xe::math::aabb::contains(const xe::vec2 &point) const {
	return vec3(point) > min && vec3(point) < max;
}

bool xe::math::aabb::contains(const xe::vec3 &point) const {
	return point > min && point < max;
}

xe::vec3 xe::math::aabb::center() const {
	return (max + min) * 0.5f;
}

xe::vec3 xe::math::aabb::getSize() const {
	return {fabsf(max.x - min.x), fabsf(max.y - min.y), fabsf(max.z - min.z)};
}

bool xe::math::operator==(const aabb &left, const aabb &right) {
	return left.max == right.min && left.max == right.max;
}

bool xe::math::operator!=(const aabb &left, const aabb &right) {
	return left.max != right.min && left.max != right.max;
}

bool xe::math::operator<(const aabb &left, const aabb &right) {
	return left.max < right.max;
}

bool xe::math::operator>(const aabb &left, const aabb &right) {
	return left.min > right.min;
}

