//
// Created by FLXR on 7/6/2018.
//

#include "glvertexbuffer.hpp"
#include "glcommon.hpp"
#include "glenums.hpp"

namespace xe { namespace internal {

	GLVertexBuffer::GLVertexBuffer(BufferUsage usage) :
			usage(usage) {

		glCall(glGenBuffers(1, &handle));
	}

	GLVertexBuffer::~GLVertexBuffer() {
		glCall(glDeleteBuffers(1, &handle));
	}

	void GLVertexBuffer::resize(uint size) {
		GLVertexBuffer::size = size;

		glCall(glBindBuffer(GL_ARRAY_BUFFER, handle));
		glCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, bufferUsageToGL(usage)));
	}

	void GLVertexBuffer::setLayout(const BufferLayout &layout) {
		GLVertexBuffer::layout = layout;
		const auto &l = layout.getLayout();

		for (uint i = 0; i < l.size(); i++) {
			auto &&element = l[i];
			glCall(glEnableVertexAttribArray(i));
			glCall(glVertexAttribPointer(i, element.count, element.type,
			                             static_cast<GLboolean>(element.normalized), layout.getStride(),
			                             reinterpret_cast<const void *> (element.offset)));
		}
	}

	void GLVertexBuffer::setData(uint size, const void *data) {
		glCall(glBindBuffer(GL_ARRAY_BUFFER, handle));
		glCall(glBufferData(GL_ARRAY_BUFFER, size, data, bufferUsageToGL(usage)));
	}

	void GLVertexBuffer::releasePointer() {
		glCall(glUnmapBuffer(GL_ARRAY_BUFFER));
	}

	void *GLVertexBuffer::getPointer() {
		glCall(void *result = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		return result;
	}

	void GLVertexBuffer::bind() {
		glCall(glBindBuffer(GL_ARRAY_BUFFER, handle));
		setLayout(layout);
	}

	void GLVertexBuffer::unbind() {
		glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

}}
