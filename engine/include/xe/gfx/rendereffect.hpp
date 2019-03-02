//
// Created by FLXR on 8/7/2018.
//

#ifndef X808_RENDEREFFECT_HPP
#define X808_RENDEREFFECT_HPP


#include <xe/xeint.hpp>

namespace xe {

	class RenderEffect {
	public:
		explicit RenderEffect(uint width, uint height) :
				enabled(true),
				width(width),
				height(height) { }

		virtual ~RenderEffect() = default;

		inline bool isEnabled() const { return enabled; }
		inline void setEnabled(bool enabled) { RenderEffect::enabled = enabled; }
		inline void toggle() { enabled = !enabled; }

	protected:
		bool enabled;

		uint width;
		uint height;
	};

}


#endif //X808_RENDEREFFECT_HPP
