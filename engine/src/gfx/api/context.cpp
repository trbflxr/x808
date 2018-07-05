//
// Created by FLXR on 6/28/2018.
//

#include "context.hpp"
#include "platform/opengl/glcontext.hpp"

xe::gfx::api::Context *xe::gfx::api::Context::context = nullptr;
xe::gfx::api::RenderAPI xe::gfx::api::Context::api = RenderAPI::NONE;

void xe::gfx::api::Context::create(const WindowProperties &props, void *deviceContext) {
	switch (getRenderAPI()) {
		case RenderAPI::OPENGL: context = new GLContext(props, deviceContext);
			break;
		default: break;
	}
}