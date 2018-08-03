//
// Created by FLXR on 6/29/2018.
//

#include "vertexbuffer.hpp"
#include "platform/opengl/glvertexbuffer.hpp"

namespace xe { namespace api {

	VertexBuffer *VertexBuffer::create(Type type) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : return new GLVertexBuffer(type);

			default: return nullptr;
		}
	}

}}