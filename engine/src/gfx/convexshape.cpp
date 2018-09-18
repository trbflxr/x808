//
// Created by FLXR on 9/18/2018.
//

#include <xe/gfx/convexshape.hpp>

namespace xe {

	ConvexShape::ConvexShape(uint pointCount) {
		setPointCount(pointCount);
	}

	void ConvexShape::setPointCount(uint count) {
		points.resize(count);
		update();
	}

	void ConvexShape::setPoint(uint index, const vec2 &point) {
		points[index] = point;
		update();
	}

	vec2 ConvexShape::getPoint(uint index) {
		return points[index];
	}

}
