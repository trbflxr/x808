//
// Created by FLXR on 8/7/2018.
//

#ifndef X808_RENDEREFFECT_HPP
#define X808_RENDEREFFECT_HPP


#include <xe/xeint.hpp>

namespace xe { namespace fx {

	class RenderEffect {
	public:
		explicit RenderEffect(uint width, uint height) :
				width(width),
				height(height) { }

		virtual ~RenderEffect() = default;

		inline uint getWidth() const { return width; }
		inline uint getHeight() const { return height; }

	protected:
		uint width;
		uint height;
	};

}}


#endif //X808_RENDEREFFECT_HPP
