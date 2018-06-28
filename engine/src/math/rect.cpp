//
// Created by FLXR on 6/28/2018.
//

#include "rect.hpp"
#include "aabb.hpp"

xe::math::rect::rect() : position(vec2()), size(vec2()) { }
xe::math::rect::rect(const xe::aabb &aabb) : position(vec2(aabb.min)), size(vec2(aabb.getSize())) { }
xe::math::rect::rect(const xe::vec2 &position, const xe::vec2 &size) : position(position), size(size) { }
xe::math::rect::rect(float x, float y, float width, float height) : position({x, y}), size({width, height}) { }

bool xe::math::rect::intersects(const xe::rect &other) {
	return (size > other.position && position < other.size) || (position > other.size && size < other.position);
}

bool xe::math::rect::contains(const xe::vec2 &point) {
	return point > getMinBound() && point < getMaxBound();
}

bool xe::math::rect::contains(const xe::vec3 &point) {
	return contains(vec2(point));
}

bool xe::math::operator==(const rect &left, const rect &right) {
	return left.position == right.position && left.size == right.size;
}

bool xe::math::operator!=(const rect &left, const rect &right) {
	return !(left ==right);
}

bool xe::math::operator>(const rect &left, const rect &right) {
	return left.size > right.size;
}

bool xe::math::operator<(const rect &left, const rect &right) {
	return left.size < right.size;
}
