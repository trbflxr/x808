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

	void GLVertexArray::drawElements(uint count) const {
		glCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
	}

	void GLVertexArray::drawArrays(uint count) const {
		glCall(glDrawArrays(GL_TRIANGLES, 0, count));
	}

	void GLVertexArray::drawArraysInstanced(uint count, uint instanceCount) const {
		glCall(glDrawArraysInstanced(GL_TRIANGLES, 0, count, instanceCount));
	}

	void GLVertexArray::pushBuffer(VertexBuffer *buffer) {
		buffers.push_back(buffer);
	}

}}