//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_VERTEXARRAY_HPP
#define X808_VERTEXARRAY_HPP


#include <xe/gfx/vertexbuffer.hpp>

namespace xe {

	namespace internal {
		class PlatformVertexArray;
	}

	class XE_API VertexArray {
	public:
		explicit VertexArray();
		~VertexArray();

		void bind() const;
		void unbind() const;

		void drawElements(uint count, BeginMode mode) const;
		void drawArrays(uint count, BeginMode mode) const;
		void drawArraysInstanced(uint count, uint instanceCount, BeginMode mode) const;

		VertexBuffer *getBuffer(uint index = 0);
		void pushBuffer(VertexBuffer *buffer);

	private:
		internal::PlatformVertexArray *array;
	};

}


#endif //X808_VERTEXARRAY_HPP
