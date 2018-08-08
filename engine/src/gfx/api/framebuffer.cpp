//
// Created by FLXR on 8/8/2018.
//

#include "framebuffer.hpp"
#include "context.hpp"
#include "platform/opengl/glframebuffer.hpp"

namespace xe { namespace api {

	FrameBuffer::FrameBuffer(const std::string_view &name) :
			name(name) { }

	FrameBuffer *FrameBuffer::create(const std::string_view &name) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : return new GLFrameBuffer(name);

			default: return nullptr;
		}
	}

}}
