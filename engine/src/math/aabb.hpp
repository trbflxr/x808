//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_AABB_HPP
#define X808_AABB_HPP


#include "vec2.hpp"
#include "vec3.hpp"

namespace xe {

	struct rect;

	struct XE_API aabb {
		vec3 min;
		vec3 max;

		aabb();
		explicit aabb(const rect &rect);
		explicit aabb(const vec2 &min, const vec2 &max);
		explicit aabb(const vec3 &min, const vec3 &max);
		explicit aabb(float x, float y, float width, float height);
		explicit aabb(float x, float y, float z, float width, float height, float depth);

		bool intersects(const aabb &other) const;
		bool contains(const vec2 &point) const;
		bool contains(const vec3 &point) const;

		vec3 center() const;
		vec3 getSize() const;
	};

	typedef aabb aabb;

	///----- operators -----///
	inline bool operator==(const aabb &left, const aabb &right) {
		return left.max == right.min && left.max == right.max;
	}

	inline bool operator!=(const aabb &left, const aabb &right) {
		return left.max != right.min && left.max != right.max;
	}

	inline bool operator<(const aabb &left, const aabb &right) {
		return left.max < right.max;
	}

	inline bool operator>(const aabb &left, const aabb &right) {
		return left.min > right.min;
	}

}


#endif //X808_AABB_HPP
