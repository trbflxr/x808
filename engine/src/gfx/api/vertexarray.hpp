//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_VERTEXARRAY_HPP
#define X808_VERTEXARRAY_HPP


#include "vertexbuffer.hpp"

namespace xe { namespace api {

	class XE_API VertexArray {
	public:
		virtual ~VertexArray() {
			for (auto &&buffer : buffers) {
				delete buffer;
			}

			buffers.clear();
		};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void drawElements(uint count, BeginMode mode) const = 0;
		virtual void drawArrays(uint count, BeginMode mode) const = 0;
		virtual void drawArraysInstanced(uint count, uint instanceCount, BeginMode mode) const = 0;

		inline VertexBuffer *getBuffer(uint index = 0) { return buffers[index]; }
		inline void pushBuffer(VertexBuffer *buffer) { buffers.push_back(buffer); };

		static VertexArray *create();

	protected:
		uint handle;

		std::vector<api::VertexBuffer *> buffers;
	};

}}


#endif //X808_VERTEXARRAY_HPP
