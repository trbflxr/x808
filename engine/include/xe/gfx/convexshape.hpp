//
// Created by FLXR on 9/18/2018.
//

#ifndef X808_CONVEXSHAPE_HPP
#define X808_CONVEXSHAPE_HPP


#include <xe/gfx/2d/shape.hpp>

namespace xe {

	class XE_API ConvexShape : public Shape {
	public:
		explicit ConvexShape(uint pointCount = 0);

		void setPointCount(uint count);
		void setPoint(uint index, const vec2 &point);

		inline uint getPointCount() const override { return (uint) points.size(); }
		inline uint getIndicesCount() const override { return 3 * (getPointCount() - 2); }

	protected:
		vec2 getPoint(uint index) override;

	private:
		std::vector<vec2> points;
	};

}


#endif //X808_CONVEXSHAPE_HPP
