//
// Created by FLXR on 8/7/2018.
//

#include "glcommon.hpp"
#include "gluniformbuffer.hpp"

namespace xe { namespace api {

	uint storageToGL(UniformBuffer::Storage storage) {
		switch (storage) {
			case UniformBuffer::DYNAMIC: return GL_DYNAMIC_STORAGE_BIT;
			case UniformBuffer::CLIENT: return GL_CLIENT_STORAGE_BIT;
		}
	}

	GLUniformBuffer::GLUniformBuffer(Storage storage, uint bindIndex, const BufferLayout &layout, uint size) {
		layouts.reserve(size);
		for (int i = 0; i < size; ++i) {
			layouts.push_back(layout);
		}

		glCall(glGenBuffers(1, &handle));

		bind();
		glCall(glBufferStorage(GL_UNIFORM_BUFFER, layout.getStride(), nullptr, storageToGL(storage)));
		unbind();

		glCall(glBindBufferBase(GL_UNIFORM_BUFFER, bindIndex, handle));
	}

	GLUniformBuffer::~GLUniformBuffer() {
		layouts.clear();
		glCall(glDeleteBuffers(1, &handle));
	}

	void GLUniformBuffer::bind() {
		glCall(glBindBuffer(GL_UNIFORM_BUFFER, handle));
	}

	void GLUniformBuffer::unbind() {
		glCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
	}

	void GLUniformBuffer::update(const void *data, uint index, uint layoutIndex) {
		auto &l = layouts[layoutIndex].getLayout();

		uint offset = l[index].offset;
		uint size = l[index].size * l[index].count;

		glCall(glNamedBufferSubData(handle, offset, size, data));
	}

}}