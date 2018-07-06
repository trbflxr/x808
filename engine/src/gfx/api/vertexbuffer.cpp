//
// Created by FLXR on 6/29/2018.
//

#include "vertexbuffer.hpp"
#include "platform/opengl/glvertexbuffer.hpp"

xe::gfx::api::VertexBuffer *xe::gfx::api::VertexBuffer::create(xe::gfx::api::BufferType type) {
	switch (Context::getRenderAPI()) {
		case RenderAPI::OPENGL : return new GLVertexBuffer(type);

		default: return nullptr;
	}
}