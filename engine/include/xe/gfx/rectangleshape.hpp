//
// Created by FLXR on 9/13/2018.
//

#ifndef X808_RECTANGLESHAPE_HPP
#define X808_RECTANGLESHAPE_HPP


#include <xe/gfx/2d/shape.hpp>

namespace xe {

	class XE_API RectangleShape : public Shape {
	public:
		explicit RectangleShape(const vec2 &size, float layer = 0.0f);

		inline const vec2 &getSize() const { return size; }
		void setSize(const vec2 &size);

		bool contains(const vec2 &point) const;

		inline bool isSizeChanged() const { return sizeChanged; }
		inline void setSizeChanged(bool changed) { sizeChanged = changed; }

		inline uint getPointCount() const override { return 4; }

	protected:
		vec2 getPoint(uint index) override;

	private:
		vec2 size;
		bool sizeChanged;
	};

}


#endif //X808_RECTANGLESHAPE_HPP
