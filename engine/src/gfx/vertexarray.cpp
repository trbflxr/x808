//
// Created by FLXR on 6/29/2018.
//

#include <xe/gfx/context.hpp>
#include <xe/gfx/vertexarray.hpp>
#include <gfx/platform/opengl/glvertexarray.hpp>

namespace xe {

	VertexArray::VertexArray() {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : {
				array = new internal::GLVertexArray();
				break;
			}

			default: {
				XE_FATAL("[VertexArray]: selected render API is not supported");
				array = nullptr;
				break;
			}
		}
	}

	VertexArray::~VertexArray() {
		delete array;
	}

	void VertexArray::bind() const {
		array->bind();
	}

	void VertexArray::unbind() const {
		array->unbind();
	}

	void VertexArray::drawElements(uint count, BeginMode mode) const {
		array->drawElements(count, mode);
	}

	void VertexArray::drawArrays(uint count, BeginMode mode) const {
		array->drawArrays(count, mode);
	}

	void VertexArray::drawArraysInstanced(uint count, uint instanceCount, BeginMode mode) const {
		array->drawArraysInstanced(count, instanceCount, mode);
	}

	VertexBuffer *VertexArray::getBuffer(uint index) {
		return array->getBuffer(index);
	}

	void VertexArray::pushBuffer(VertexBuffer *buffer) {
		array->pushBuffer(buffer);
	};

}