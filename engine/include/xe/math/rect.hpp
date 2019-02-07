//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_RECT_HPP
#define X808_RECT_HPP


#include <xe/math/vec2.hpp>
#include <xe/math/vec3.hpp>

namespace xe {

	struct aabb;

	struct XE_API rect {
		union {
			vec2 position;
			struct {
				float x;
				float y;
			};
		};
		union {
			vec2 size;
			struct {
				float width;
				float height;
			};
		};

		rect();
		rect(const rect &other);
		explicit rect(const aabb &aabb);
		rect(const vec2 &position, const vec2 &size);
		rect(float x, float y, float width, float height);

		bool intersects(const rect &other) const;
		bool contains(const vec2 &point) const;
		bool contains(const vec3 &point) const;

		inline vec2 getMinBound() const { return position - size; }
		inline vec2 getMaxBound() const { return position + size; }
	};

	typedef rect rect;

	///----- operators -----///
	inline bool operator==(const rect &left, const rect &right) {
		return left.position == right.position && left.size == right.size;
	}

	inline bool operator!=(const rect &left, const rect &right) {
		return !(left == right);
	}

	inline bool operator>(const rect &left, const rect &right) {
		return left.size > right.size;
	}

	inline bool operator<(const rect &left, const rect &right) {
		return left.size < right.size;
	}

}


#endif //X808_RECT_HPP
