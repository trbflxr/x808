//
// Created by FLXR on 7/6/2018.
//

#include "glvertexarray.hpp"
#include "glcommon.hpp"
#include "glenums.hpp"

namespace xe { namespace api {

	void GLVertexArray::bind() const {
		buffers.front()->bind();
	}

	void GLVertexArray::unbind() const {
		buffers.front()->unbind();
	}

	void GLVertexArray::drawElements(uint count, BeginMode mode) const {
		glCall(glDrawElements(beginModeToGL(mode), count, GL_UNSIGNED_INT, nullptr));
	}

	void GLVertexArray::drawArrays(uint count, BeginMode mode) const {
		glCall(glDrawArrays(beginModeToGL(mode), 0, count));
	}

	void GLVertexArray::drawArraysInstanced(uint count, uint instanceCount, BeginMode mode) const {
		glCall(glDrawArraysInstanced(beginModeToGL(mode), 0, count, instanceCount));
	}

	void GLVertexArray::pushBuffer(VertexBuffer *buffer) {
		buffers.push_back(buffer);
	}

}}