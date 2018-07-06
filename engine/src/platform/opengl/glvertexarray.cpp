//
// Created by FLXR on 7/6/2018.
//

#include "glvertexarray.hpp"
#include "glcommon.hpp"

void xe::gfx::api::GLVertexArray::bind() const {
	buffers.front()->bind();
}

void xe::gfx::api::GLVertexArray::unbind() const {
	buffers.front()->unbind();
}

void xe::gfx::api::GLVertexArray::draw(uint count) const {
	glCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
}

void xe::gfx::api::GLVertexArray::pushBuffer(xe::gfx::api::VertexBuffer *buffer) {
	buffers.push_back(buffer);
}