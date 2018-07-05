//
// Created by FLXR on 6/29/2018.
//

#include "renderer.hpp"
#include "gfx/api/context.hpp"
#include "platform/opengl/glrenderer.hpp"

xe::gfx::Renderer *xe::gfx::Renderer::instance = nullptr;
uint xe::gfx::Renderer::dc = 0;

void xe::gfx::Renderer::init() {
	dc = 0;
	switch (api::Context::getRenderAPI()) {
		case api::RenderAPI::OPENGL : instance = new GLRenderer();
			break;

		default:break;
	}

	instance->initInternal();
}