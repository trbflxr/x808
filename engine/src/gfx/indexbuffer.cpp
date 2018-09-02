//
// Created by FLXR on 6/29/2018.
//

#include <xe/gfx/context.hpp>
#include <xe/utils/log.hpp>
#include <xe/gfx/indexbuffer.hpp>
#include <gfx/platform/opengl/glindexbuffer.hpp>

namespace xe {

	IndexBuffer::IndexBuffer(const uint16 *data, uint count) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : {
				buffer = new internal::GLIndexBuffer(data, count);
				break;
			}

			default: {
				XE_FATAL("[IndexBuffer]: selected render API is not supported");
				buffer = nullptr;
				break;
			}
		}
	}

	IndexBuffer::IndexBuffer(const uint *data, uint count) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : {
				buffer = new internal::GLIndexBuffer(data, count);
				break;
			}

			default: {
				XE_FATAL("[IndexBuffer]: selected render API is not supported");
				buffer = nullptr;
				break;
			}
		}
	}

	IndexBuffer::~IndexBuffer() {
		delete buffer;
	}

	void IndexBuffer::bind() const {
		buffer->bind();
	}

	void IndexBuffer::unbind() const {
		buffer->unbind();
	}

	uint IndexBuffer::getCount() const {
		return buffer->getCount();
	}

}