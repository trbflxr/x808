//
// Created by FLXR on 7/6/2018.
//

#include "glvertexbuffer.hpp"
#include "glcommon.hpp"

static uint bufferTypeToOpenGL(xe::gfx::api::BufferType type) {
	switch (type) {
		case xe::gfx::api::BufferType::STATIC: return GL_STATIC_DRAW;
		case xe::gfx::api::BufferType::DYNAMIC: return GL_DYNAMIC_DRAW;
	}
}

xe::gfx::api::GLVertexBuffer::GLVertexBuffer(xe::gfx::api::BufferType type) :
		type(type) {

	glCall(glGenBuffers(1, &handle));
}

xe::gfx::api::GLVertexBuffer::~GLVertexBuffer() {
	glCall(glDeleteBuffers(1, &handle));
}

void xe::gfx::api::GLVertexBuffer::resize(uint size) {
	GLVertexBuffer::size = size;

	glCall(glBindBuffer(GL_ARRAY_BUFFER, handle));
	glCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, bufferTypeToOpenGL(type)));
}

void xe::gfx::api::GLVertexBuffer::setLayout(const xe::gfx::api::BufferLayout &layout) {
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

void xe::gfx::api::GLVertexBuffer::setData(uint size, const void *data) {
	glCall(glBindBuffer(GL_ARRAY_BUFFER, handle));
	glCall(glBufferData(GL_ARRAY_BUFFER, size, data, bufferTypeToOpenGL(type)));
}

void xe::gfx::api::GLVertexBuffer::releasePointer() {
	glCall(glUnmapBuffer(GL_ARRAY_BUFFER));
}

void xe::gfx::api::GLVertexBuffer::bind() {
	glCall(glBindBuffer(GL_ARRAY_BUFFER, handle));
	setLayout(layout);
}

void xe::gfx::api::GLVertexBuffer::unbind() {
	glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void *xe::gfx::api::GLVertexBuffer::getPointerInternal() {
	glCall(void *result = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	return result;
}
