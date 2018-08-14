//
// Created by FLXR on 7/6/2018.
//

#include "glindexbuffer.hpp"
#include "glcommon.hpp"

namespace xe { namespace api {

	GLIndexBuffer::GLIndexBuffer(const uint16 *data, uint count) :
			count(count) {

		glCall(glGenBuffers(1, &handle));
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
		glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint16), data, GL_STATIC_DRAW));
	}

	GLIndexBuffer::GLIndexBuffer(const uint *data, uint count) :
			count(count) {

		glCall(glGenBuffers(1, &handle));
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
		glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));
	}

	GLIndexBuffer::~GLIndexBuffer() {
		glCall(glDeleteBuffers(1, &handle));
	}

	void GLIndexBuffer::bind() const {
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
	}

	void GLIndexBuffer::unbind() const {
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

}}