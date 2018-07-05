//
// Created by FLXR on 6/29/2018.
//

#include "indexbuffer.hpp"
#include "platform/opengl/glcommon.hpp"

xe::gfx::api::IndexBuffer::IndexBuffer(uint16 *data, uint count) {
	glCall(glGenBuffers(1, &handle));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint16), data, GL_STATIC_DRAW));
}

xe::gfx::api::IndexBuffer::IndexBuffer(uint *data, uint count) {
	glCall(glGenBuffers(1, &handle));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));
}

xe::gfx::api::IndexBuffer::~IndexBuffer() {
	glCall(glDeleteBuffers(1, &handle));
}

void xe::gfx::api::IndexBuffer::bind() const {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
}

void xe::gfx::api::IndexBuffer::unbind() const {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
