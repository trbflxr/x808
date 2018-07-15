//
// Created by FLXR on 6/28/2018.
//

#include "rect.hpp"
#include "aabb.hpp"

namespace xe {

	rect::rect() : position(vec2()), size(vec2()) { }
	rect::rect(const xe::aabb &aabb) : position(vec2(aabb.min)), size(vec2(aabb.getSize())) { }
	rect::rect(const xe::vec2 &position, const xe::vec2 &size) : position(position), size(size) { }
	rect::rect(float x, float y, float width, float height) : position(x, y), size(width, height) { }

	bool rect::intersects(const xe::rect &other) {
		return (size > other.position && position < other.size) || (position > other.size && size < other.position);
	}

	bool rect::contains(const xe::vec2 &point) {
		return point > getMinBound() && point < getMaxBound();
	}

	bool rect::contains(const xe::vec3 &point) {
		return contains(vec2(point));
	}

}