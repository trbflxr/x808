//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_PLATFORMVERTEXARRAY_HPP
#define X808_PLATFORMVERTEXARRAY_HPP


#include <xe/gfx/vertexarray.hpp>

namespace xe { namespace internal {

	class PlatformVertexArray {
	public:
		virtual ~PlatformVertexArray() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void drawElements(uint count, BeginMode mode) const = 0;
		virtual void drawArrays(uint count, BeginMode mode) const = 0;
		virtual void drawArraysInstanced(uint count, uint instanceCount, BeginMode mode) const = 0;

		virtual VertexBuffer *getBuffer(uint index) = 0;
		virtual void pushBuffer(VertexBuffer *buffer) = 0;
	};

}}


#endif //X808_PLATFORMVERTEXARRAY_HPP
