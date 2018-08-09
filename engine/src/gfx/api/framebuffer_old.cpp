//
// Created by FLXR on 7/24/2018.
//

#include "framebuffer_old.hpp"
#include "context.hpp"
#include "platform/opengl/glframebuffer_old.hpp"

namespace xe { namespace api {

	FrameBufferOld *FrameBufferOld::create(uint width, uint height, Type type, TextureMinFilter filter) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : return new GLFrameBufferOld(width, height, type, filter);

			default: return nullptr;
		}
	}

}}
