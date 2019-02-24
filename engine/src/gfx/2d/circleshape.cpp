//
// Created by FLXR on 9/17/2018.
//

#include <xe/gfx/2d/circleshape.hpp>

namespace xe {

	CircleShape::CircleShape(float radius, uint pointCount) :
			Shape(),
			radius(radius),
			pointCount(pointCount),
			radiusChanged(true) {

		setRadius(radius);
	}


	void CircleShape::setRadius(float radius) {
		CircleShape::radius = radius;
		radiusChanged = true;

		setOrigin(vec2(radius / 2.0f));

		update();
	}

	vec2 CircleShape::getPoint(uint index) {
		const float angle = index * 2.0f * XE_PI / pointCount - XE_PI / 2.0f;
		const float x = cosf(angle) * radius;
		const float y = sinf(angle) * radius;

		return vec2(radius / 2.0f + x, radius / 2.0f + y);
	}

}