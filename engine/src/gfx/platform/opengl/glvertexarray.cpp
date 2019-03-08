//
// Created by FLXR on 7/6/2018.
//

#include <GL/glew.h>
#include "glcommon.hpp"
#include "glenums.hpp"
#include "glvertexarray.hpp"

namespace xe { namespace internal {

	GLVertexArray::~GLVertexArray() {
		for (const auto &b : buffers) {
			delete b;
		}
		buffers.clear();
	}

	void GLVertexArray::bind() const {
		buffers.front()->bind();
	}

	void GLVertexArray::unbind() const {
		buffers.front()->unbind();
	}

	void GLVertexArray::drawElements(uint count, BeginMode mode, const void *indices) const {
		glCall(glDrawElements(beginModeToGL(mode), count, GL_UNSIGNED_INT, indices));
	}

	void GLVertexArray::drawElementsInstanced(uint count, BeginMode mode, uint instances, const void *indices) const {
		glCall(glDrawElementsInstanced(beginModeToGL(mode), count, GL_UNSIGNED_INT, indices, instances));
	}

	void GLVertexArray::drawArrays(uint count, BeginMode mode) const {
		glCall(glDrawArrays(beginModeToGL(mode), 0, count));
	}

	void GLVertexArray::drawArraysInstanced(uint count, uint instanceCount, BeginMode mode) const {
		glCall(glDrawArraysInstanced(beginModeToGL(mode), 0, count, instanceCount));
	}

}}