//
// Created by FLXR on 9/13/2018.
//

#include <xe/gfx/sprite.hpp>
#include <xe/gfx/rectangleshape.hpp>

namespace xe {

	RectangleShape::RectangleShape(const vec2 &size) :
			size(size),
			sizeChanged(true) {

		setSize(size);
	}

	void RectangleShape::setSize(const vec2 &size) {
		RectangleShape::size = size;
		sizeChanged = true;

		setOrigin(size / 2.0f);

		update();
	}

	vec2 RectangleShape::getPoint(uint index) {
		switch (index) {
			default:
			case 0: return vec2(0.0f, 0.0f);
			case 1: return vec2(size.x, 0.0f);
			case 2: return vec2(size.x, size.y);
			case 3: return vec2(0.0f, size.y);
		}
	}

}