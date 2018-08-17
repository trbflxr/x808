//
// Created by FLXR on 8/4/2018.
//

#ifndef X808_DEFERREDRENDERER_HPP
#define X808_DEFERREDRENDERER_HPP


#include <xe/common.hpp>
#include <xe/gfx/camera.hpp>

namespace xe {

	class XE_API DeferredRenderer {
	public:
		explicit DeferredRenderer(uint width, uint height, Camera *camera) { }
		~DeferredRenderer() { }

		void begin() { }
		void submit() { }
		void flush() { }

	};

}


#endif //X808_DEFERREDRENDERER_HPP
