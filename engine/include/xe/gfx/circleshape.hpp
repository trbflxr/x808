//
// Created by FLXR on 9/17/2018.
//

#ifndef X808_CIRCLESHAPE_HPP
#define X808_CIRCLESHAPE_HPP


#include <xe/gfx/2d/shape.hpp>

namespace xe {

	class XE_API CircleShape : public Shape {
	public:
		explicit CircleShape(float radius, float layer = 0.0f, uint pointCount = 30);

		inline float getRadius() const { return radius; }
		inline void setRadius(float radius);

		inline bool isRadiusChanged() const { return radiusChanged; }
		inline void setRadiusChanged(bool changed) { radiusChanged = changed; }

		inline uint getPointCount() const override { return pointCount; }

	protected:
		vec2 getPoint(uint index) override;

	private:
		float radius;
		uint pointCount;

		bool radiusChanged;
	};

}


#endif //X808_CIRCLESHAPE_HPP
