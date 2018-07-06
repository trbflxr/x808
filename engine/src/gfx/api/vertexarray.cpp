//
// Created by FLXR on 6/29/2018.
//

#include "vertexarray.hpp"
#include "platform/opengl/glvertexarray.hpp"

xe::gfx::api::VertexArray *xe::gfx::api::VertexArray::create() {
	switch (Context::getRenderAPI()) {
		case RenderAPI::OPENGL: return new GLVertexArray();

		default: return nullptr;
	}
}
