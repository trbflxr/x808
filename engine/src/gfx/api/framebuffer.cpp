//
// Created by FLXR on 7/24/2018.
//

#include "framebuffer.hpp"
#include "context.hpp"
#include "platform/opengl/glframebuffer.hpp"

namespace xe { namespace api {

	FrameBuffer *FrameBuffer::create(uint width, uint height, Type type, TextureFilter filter) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : return new GLFrameBuffer(width, height, type, filter);

			default: return nullptr;
		}
	}

}}
