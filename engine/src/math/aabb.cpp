//
// Created by FLXR on 6/28/2018.
//

#include <xe/math/aabb.hpp>
#include <xe/math/math.hpp>

namespace xe {

	aabb::aabb() : min(vec3()), max(vec3()) { }
	aabb::aabb(const rect &rect) : min(rect.getMinBound()), max(rect.getMaxBound()) { }
	aabb::aabb(const vec2 &min, const vec2 &max) : min(min), max(max) { }
	aabb::aabb(const vec3 &min, const vec3 &max) : min(min), max(max) { }
	aabb::aabb(float x, float y, float width, float height) : min(x, y, 0.0f), max(width, height, 0.0f) { }
	aabb::aabb(float x, float y, float z, float w, float h, float depth) : min(x, y, z), max(w, h, depth) { }

	bool aabb::intersects(const aabb &other) const {
		return (max > other.min && min < other.max) || (min > other.max && max < other.min);
	}

	bool aabb::contains(const vec2 &point) const {
		return vec3(point) > min && vec3(point) < max;
	}

	bool aabb::contains(const vec3 &point) const {
		return point > min && point < max;
	}

	vec3 aabb::center() const {
		return (max + min) * 0.5f;
	}

	vec3 aabb::getSize() const {
		return {fabsf(max.x - min.x), fabsf(max.y - min.y), fabsf(max.z - min.z)};
	}

}

