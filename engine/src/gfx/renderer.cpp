//
// Created by FLXR on 6/29/2018.
//

#include <xe/gfx/context.hpp>
#include <xe/gfx/renderer.hpp>
#include <gfx/platform/opengl/glrenderer.hpp>

namespace xe {

	Renderer *Renderer::instance = nullptr;
	uint Renderer::dc = 0;

	void Renderer::init() {
		dc = 0;
		switch (Context::getRenderAPI()) {
			case RenderAPI::OpenGL : instance = new internal::GLRenderer();
				break;

			default:break;
		}

		instance->initInternal();
	}

}