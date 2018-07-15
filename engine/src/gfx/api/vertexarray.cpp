//
// Created by FLXR on 6/29/2018.
//

#include "vertexarray.hpp"
#include "platform/opengl/glvertexarray.hpp"

namespace xe { namespace gfx { namespace api {

	VertexArray *VertexArray::create() {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL: return new GLVertexArray();

			default: return nullptr;
		}
	}

}}}