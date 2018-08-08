//
// Created by FLXR on 8/7/2018.
//

#ifndef X808_RENDEREFFECT_HPP
#define X808_RENDEREFFECT_HPP


#include "xeint.hpp"

namespace xe { namespace fx {

	class RenderEffect {
	public:
		explicit RenderEffect(uint width, uint height) :
				enabled(true),
				width(width),
				height(height),
				halfWidth(width / 2),
				halfHeight(height / 2) { }


		inline bool isEnabled() const { return enabled; }
		inline void setEnabled(bool enabled) { RenderEffect::enabled = enabled; }

		inline void toggle() { enabled = !enabled; }

		virtual void load() = 0;
		virtual void unload() = 0;
		virtual void reload() = 0;

	protected:
		virtual void loadPrograms() = 0;
		virtual void loadBuffers() = 0;

	protected:
		bool enabled;

		uint width;
		uint height;

		uint halfWidth;
		uint halfHeight;
	};

}}


#endif //X808_RENDEREFFECT_HPP
