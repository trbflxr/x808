//
// Created by FLXR on 7/2/2018.
//

#ifndef X808_AOBB_HPP
#define X808_AOBB_HPP


#include <array>
#include <xe/math/vec2.hpp>

namespace xe {

	class XE_API aobb {
	public:
		aobb();
		explicit aobb(const vec2 &position, const vec2 &size, float rotation = 0.0f);
		explicit aobb(float x, float y, float width, float height, float rotation = 0.0f);
		aobb(const aobb &other);

		bool contains(const vec2 &point) const;

		void move(const vec2 &direction);
		void rotate(float deg);

		inline const vec2 &getPosition() const { return position; }
		inline const vec2 &getSize() const { return size; }
		inline const float getRotation() const { return rotation; }
		const std::array<vec2, 4> &getVertices() const;

		void setPosition(const vec2 &position);
		void setPosition(float x, float y);
		void setSize(const vec2 &size);
		void setSize(float width, float height);
		void setRotation(float deg);

	private:
		mutable bool transformed;

		vec2 position;
		vec2 size;
		float rotation;

		mutable std::array<vec2, 4> vertices;
	};

	typedef aobb aobb;
}


#endif //X808_AOBB_HPP
