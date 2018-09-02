//
// Created by FLXR on 9/1/2018.
//

#include <gfx/platform/opengl/glstoragebuffer.hpp>
#include <xe/gfx/storagebuffer.hpp>

namespace xe {

	StorageBuffer::StorageBuffer(uint size) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : {
				buffer = new internal::GLStorageBuffer(size);
				break;
			}

			default: {
				XE_FATAL("[StorageBuffer]: selected render API is not supported");
				buffer = nullptr;
				break;
			}
		}
	}

	StorageBuffer::~StorageBuffer() {
		delete buffer;
	}

	void StorageBuffer::update(const void *data, uint size) {
		buffer->update(data, size);
	}

	void StorageBuffer::bind() {
		buffer->bind();
	}

	void StorageBuffer::bind(uint index) {
		buffer->bind(index);
	}

	void StorageBuffer::unbind() {
		buffer->unbind();
	}

	void StorageBuffer::unbind(uint index) {
		buffer->unbind(index);
	}

	uint StorageBuffer::getHandle() {
		return buffer->getHandle();
	}

}