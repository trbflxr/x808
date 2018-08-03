//
// Created by FLXR on 7/6/2018.
//

#include "glvertexarray.hpp"
#include "glcommon.hpp"

namespace xe { namespace api {

	void GLVertexArray::bind() const {
		buffers.front()->bind();
	}

	void GLVertexArray::unbind() const {
		buffers.front()->unbind();
	}

	void GLVertexArray::draw(uint count) const {
		glCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
	}

	void GLVertexArray::pushBuffer(VertexBuffer *buffer) {
		buffers.push_back(buffer);
	}

}}