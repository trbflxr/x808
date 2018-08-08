//
// Created by FLXR on 8/7/2018.
//

#include "uniformbuffer.hpp"
#include "platform/opengl/gluniformbuffer.hpp"

namespace xe { namespace api {

	UniformBuffer *UniformBuffer::create(Storage storage, uint bindIndex, const BufferLayout &layout, uint size) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : return new GLUniformBuffer(storage, bindIndex, layout, size);

			default: return nullptr;
		}
	}

}}
