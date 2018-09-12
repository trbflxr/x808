//
// Created by FLXR on 8/7/2018.
//

#include <xe/gfx/uniformbuffer.hpp>
#include <xe/gfx/context.hpp>
#include <gfx/platform/opengl/gluniformbuffer.hpp>

namespace xe {

	UniformBuffer::UniformBuffer(BufferStorage storage, uint bind, const BufferLayout &layout, uint size) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OpenGL : {
				buffer = new internal::GLUniformBuffer(storage, bind, layout, size);
				break;
			}

			default: {
				XE_FATAL("[UniformBuffer]: selected render API is not supported");
				buffer = nullptr;
				break;
			}
		}
	}

	UniformBuffer::~UniformBuffer() {
		delete buffer;
	}

	void UniformBuffer::bind() {
		buffer->bind();
	}

	void UniformBuffer::unbind() {
		buffer->unbind();
	}

	void UniformBuffer::update(const void *data, uint index, uint layoutIndex) {
		buffer->update(data, index, layoutIndex);
	}

	uint UniformBuffer::getHandle() const {
		return buffer->getHandle();
	}

}
