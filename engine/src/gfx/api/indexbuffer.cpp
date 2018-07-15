//
// Created by FLXR on 6/29/2018.
//

#include "indexbuffer.hpp"
#include "platform/opengl/glindexbuffer.hpp"
#include "context.hpp"

namespace xe { namespace gfx { namespace api {

	IndexBuffer *IndexBuffer::create(const uint16 *data, uint count) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL: return new GLIndexBuffer(data, count);

			default: return nullptr;
		}
	}

	IndexBuffer *IndexBuffer::create(const uint *data, uint count) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL: return new GLIndexBuffer(data, count);

			default: return nullptr;
		}
	}

}}}