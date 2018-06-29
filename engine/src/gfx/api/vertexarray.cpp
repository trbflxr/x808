//
// Created by FLXR on 6/29/2018.
//

#include "vertexarray.hpp"
#include "gfx/glcommon.hpp"

void xe::gfx::api::VertexArray::bind() const {
	buffers.front()->bind();
}

void xe::gfx::api::VertexArray::unbind() const {
	buffers.front()->unbind();
}

void xe::gfx::api::VertexArray::draw(uint count) const {
	glCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
}

void xe::gfx::api::VertexArray::pushBuffer(xe::gfx::api::VertexBuffer *buffer) {
	buffers.push_back(buffer);
}
