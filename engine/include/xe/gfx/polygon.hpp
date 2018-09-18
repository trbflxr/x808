//
// Created by FLXR on 9/18/2018.
//

#ifndef X808_POLYGON_HPP
#define X808_POLYGON_HPP


#include <xe/gfx/2d/shape.hpp>

namespace xe {

	class XE_API Polygon : public Shape {
	public:
		explicit Polygon(uint pointCount = 0);

		void setPointCount(uint count);
		void setPoint(uint index, const vec2 &point);

		void create();

		inline uint getPointCount() const override { return (uint) polygon[0].size(); }

	protected:
		vec2 getPoint(uint index) override;

	private:
		std::vector<std::vector<std::array<float, 2>>> polygon;
	};

}


#endif //X808_POLYGON_HPP
