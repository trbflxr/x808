//
// Created by FLXR on 6/28/2018.
//

#include "context.hpp"
#include "platform/opengl/glcontext.hpp"

namespace xe { namespace api {

	Context *Context::context = nullptr;
	RenderAPI Context::api = RenderAPI::NONE;

	void Context::create(void *deviceContext) {
		switch (getRenderAPI()) {
			case RenderAPI::OPENGL: context = new GLContext(deviceContext);
				break;
			default: break;
		}
	}

}}