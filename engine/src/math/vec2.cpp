//
// Created by FLXR on 6/28/2018.
//

#include <xe/math/vec2.hpp>
#include <xe/math/math.hpp>

namespace xe {

	vec2::vec2() : x(0), y(0) { }
	vec2::vec2(float x, float y) : x(x), y(y) { }
	vec2::vec2(const vec2 &other) : x(other.x), y(other.y) { }
	vec2::vec2(const vec3 &other) : x(other.x), y(other.y) { }

	vec2 vec2::normalize() {
		const float l = length(*this);
		x /= l;
		y /= l;
		return *this;
	}

	///----- static -----///
	float vec2::length(const vec2 &v) {
		return sqrtf(v.x * v.x + v.y * v.y);
	}

	float vec2::max(const vec2 &v) {
		return v.x > v.y ? v.x : v.y;
	}

	float vec2::dot(const vec2 &v1, const vec2 &v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}

	vec2 vec2::normalize(const vec2 &v) {
		const float l = length(v);
		return vec2(v.x / l, v.y / l);
	}

	float vec2::cross(const vec2 &v1, const vec2 &v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}

	vec2 vec2::lerp(const vec2 &v, const vec2 &dest, float lerpFactor) {
		return (dest - v) * lerpFactor + v;
	}

	vec2 vec2::rotate(const vec2 &v, float angle) {
		const float rad = to_rad(angle);
		const float cos = cosf(rad);
		const float sin = sinf(rad);

		return vec2(v.x * cos - v.y * sin, v.x * sin + v.y * cos);
	}

}
