//
// Created by FLXR on 6/28/2018.
//

#include <xe/math/rect.hpp>
#include <xe/math/aabb.hpp>

namespace xe {

	rect::rect() : position(0.0f, 0.0f), size(0.0f, 0.0f) { }
	rect::rect(const aabb &aabb) : position(vec2(aabb.min)), size(vec2(aabb.getSize())) { }
	rect::rect(const vec2 &position, const vec2 &size) : position(position), size(size) { }
	rect::rect(float x, float y, float width, float height) : position(x, y), size(width, height) { }

	bool rect::intersects(const rect &other) {
		return (size > other.position && position < other.size) || (position > other.size && size < other.position);
	}

	bool rect::contains(const vec2 &point) {
		return point > getMinBound() && point < getMaxBound();
	}

	bool rect::contains(const vec3 &point) {
		return contains(vec2(point));
	}

}