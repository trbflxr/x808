//
// Created by FLXR on 8/7/2018.
//

#include "glcommon.hpp"
#include "glenums.hpp"
#include "gluniformbuffer.hpp"

namespace xe { namespace internal {

	GLUniformBuffer::GLUniformBuffer(BufferStorage storage, uint bind, const BufferLayout &layout, uint size) {
		layouts.reserve(size);
		for (int i = 0; i < size; ++i) {
			layouts.push_back(layout);
		}

		glCall(glGenBuffers(1, &handle));

		GLUniformBuffer::bind();
		glCall(glBufferStorage(GL_UNIFORM_BUFFER, layout.getStride(), nullptr, bufferStorageToGL(storage)));
		unbind();

		glCall(glBindBufferBase(GL_UNIFORM_BUFFER, bind, handle));
	}

	GLUniformBuffer::~GLUniformBuffer() {
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