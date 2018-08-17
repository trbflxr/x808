//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_VERTEXBUFFER_HPP
#define X808_VERTEXBUFFER_HPP


#include <xe/common.hpp>
#include <xe/gfx/enums.hpp>
#include <xe/gfx/bufferlayout.hpp>

namespace xe {

	namespace internal {
		class PlatformVertexBuffer;
	}

	class XE_API VertexBuffer {
	public:
		explicit VertexBuffer(BufferUsage usage = BufferUsage::StaticDraw);
		~VertexBuffer();

		void resize(uint size);
		void setLayout(const BufferLayout &layout);
		void setData(uint size, const void *data);

		void releasePointer();
		void *getPointer();

		void bind();
		void unbind();

	private:
		internal::PlatformVertexBuffer *buffer;
	};

}


#endif //X808_VERTEXBUFFER_HPP
