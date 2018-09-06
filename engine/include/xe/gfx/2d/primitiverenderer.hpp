//
// Created by FLXR on 9/6/2018.
//

#ifndef X808_PRIMITIVERENDERER_HPP
#define X808_PRIMITIVERENDERER_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/math/vec2.hpp>
#include <xe/math/rect.hpp>
#include <xe/gfx/color.hpp>
#include <xe/gfx/2d/irenderer2d.hpp>

namespace xe {

	class XE_API PrimitiveRenderer : public IRenderer2D {
	public:
		explicit PrimitiveRenderer(uint width, uint height);
		~PrimitiveRenderer() override = default;

		void begin() override;
		void end() override;
		void flush() override;

		void drawLine(float x0, float y0, float x1, float y1, float z,
		              uint color = color::WHITE, float thickness = 0.02f);

		void drawLine(const vec2 &start, const vec2 &end, float z,
		              uint color = color::WHITE, float thickness = 0.02f);

		void drawRect(float x, float y, float width, float height, float z, uint color = color::WHITE);
		void drawRect(const vec2 &position, const vec2 &size, float z, uint color = color::WHITE);
		void drawRect(const rect &rectangle, float z, uint color = color::WHITE);

		void fillRect(float x, float y, float width, float height, float z, uint color = color::WHITE);
		void fillRect(const vec2 &position, const vec2 &size, float z, uint color = color::WHITE);
		void fillRect(const rect &rectangle, float z, uint color = color::WHITE);

	};

}


#endif //X808_PRIMITIVERENDERER_HPP
