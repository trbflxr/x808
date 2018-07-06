//
// Created by FLXR on 6/29/2018.
//

#include "indexbuffer.hpp"
#include "platform/opengl/glindexbuffer.hpp"
#include "context.hpp"

xe::gfx::api::IndexBuffer *xe::gfx::api::IndexBuffer::create(uint16 *data, uint count) {
	switch (Context::getRenderAPI()) {
		case RenderAPI::OPENGL: return new GLIndexBuffer(data, count);

		default: return nullptr;
	}
}

xe::gfx::api::IndexBuffer *xe::gfx::api::IndexBuffer::create(uint *data, uint count) {
	switch (Context::getRenderAPI()) {
		case RenderAPI::OPENGL: return new GLIndexBuffer(data, count);

		default: return nullptr;
	}
}
