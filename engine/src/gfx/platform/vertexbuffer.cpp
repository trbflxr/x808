//
// Created by FLXR on 6/29/2018.
//

#include <xe/gfx/vertexbuffer.hpp>
#include <xe/gfx/context.hpp>
#include <gfx/platform/opengl/glvertexbuffer.hpp>

namespace xe {

	VertexBuffer::VertexBuffer(BufferUsage usage) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : {
				buffer = new internal::GLVertexBuffer(usage);
				break;
			}

			default: {
				XE_FATAL("[VertexBuffer]: selected render API is not supported");
				buffer = nullptr;
				break;
			}
		}
	}

	VertexBuffer::~VertexBuffer() {
		delete buffer;
	}

	void VertexBuffer::resize(uint size) {
		buffer->resize(size);
	}

	void VertexBuffer::setLayout(const BufferLayout &layout) {
		buffer->setLayout(layout);
	}

	void VertexBuffer::setData(uint size, const void *data) {
		buffer->setData(size, data);
	}

	void VertexBuffer::releasePointer() {
		buffer->releasePointer();
	}

	void *VertexBuffer::getPointer() {
		return buffer->getPointer();
	}

	void VertexBuffer::bind() {
		buffer->bind();
	}

	void VertexBuffer::unbind() {
		buffer->unbind();
	}

}