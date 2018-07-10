//
// Created by FLXR on 7/6/2018.
//

#include "glindexbuffer.hpp"
#include "glcommon.hpp"

xe::gfx::api::GLIndexBuffer::GLIndexBuffer(uint16 *data, uint count) {
	glCall(glGenBuffers(1, &handle));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint16), data, GL_STATIC_DRAW));
}

xe::gfx::api::GLIndexBuffer::GLIndexBuffer(uint *data, uint count) {
	glCall(glGenBuffers(1, &handle));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));
}

xe::gfx::api::GLIndexBuffer::~GLIndexBuffer() {
	glCall(glDeleteBuffers(1, &handle));
}

void xe::gfx::api::GLIndexBuffer::bind() const {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
}

void xe::gfx::api::GLIndexBuffer::unbind() const {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}