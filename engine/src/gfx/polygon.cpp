//
// Created by FLXR on 9/18/2018.
//

#include <earcut/earcut.hpp>
#include <xe/gfx/polygon.hpp>

namespace xe {

	Polygon::Polygon(uint pointCount, float layer) :
			Shape(layer) {

		polygon.resize(1);
		setPointCount(pointCount);
	}

	void Polygon::create() {
		if (polygon[0].size() < 3) return;

		setIndices(mapbox::earcut(polygon));

		update(false);
	}

	void Polygon::setPointCount(uint count) {
		polygon[0].resize(count);
	}

	void Polygon::setPoint(uint index, const vec2 &point) {
		polygon[0][index][0] = point.x;
		polygon[0][index][1] = point.y;
	}

	vec2 Polygon::getPoint(uint index) {
		return vec2(polygon[0][index][0], polygon[0][index][1]);
	}

}
