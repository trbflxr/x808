//
// Created by FLXR on 7/6/2018.
//

#include "glvertexbuffer.hpp"
#include "glcommon.hpp"

namespace xe { namespace api {

	static uint bufferTypeToOpenGL(VertexBuffer::Type type) {
		switch (type) {
			case VertexBuffer::Type::STATIC: return GL_STATIC_DRAW;
			case VertexBuffer::Type::DYNAMIC: return GL_DYNAMIC_DRAW;
		}
	}

	GLVertexBuffer::GLVertexBuffer(Type type) :
			type(type) {

		glCall(glGenBuffers(1, &handle));
	}

	GLVertexBuffer::~GLVertexBuffer() {
		glCall(glDeleteBuffers(1, &handle));
	}

	void GLVertexBuffer::resize(uint size) {
		GLVertexBuffer::size = size;

		glCall(glBindBuffer(GL_ARRAY_BUFFER, handle));
		glCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, bufferTypeToOpenGL(type)));
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
		glCall(glBufferData(GL_ARRAY_BUFFER, size, data, bufferTypeToOpenGL(type)));
	}

	void GLVertexBuffer::releasePointer() {
		glCall(glUnmapBuffer(GL_ARRAY_BUFFER));
	}

	void GLVertexBuffer::bind() {
		glCall(glBindBuffer(GL_ARRAY_BUFFER, handle));
		setLayout(layout);
	}

	void GLVertexBuffer::unbind() {
		glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void *GLVertexBuffer::getPointerInternal() {
		glCall(void *result = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		return result;
	}

}}
