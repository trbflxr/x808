//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_VERTEXBUFFER_HPP
#define X808_VERTEXBUFFER_HPP


#include "common.hpp"
#include "bufferlayout.hpp"

namespace xe { namespace gfx { namespace api {

	enum class BufferType {
		STATIC, DYNAMIC
	};

	class XE_API VertexBuffer {
	public:
		explicit VertexBuffer(BufferType type);
		~VertexBuffer();

		void resize(uint size);
		void setLayout(const BufferLayout &layout);
		void setData(uint size, const void *data);

		void releasePointer();

		void bind();
		void unbind();

		template<typename T>
		T *getPointer() { return (T *) getPointerInternal(); }

	private:
		void *getPointerInternal();

	private:
		uint handle;
		uint size;
		BufferType type;
		BufferLayout layout;
	};

}}}


#endif //X808_VERTEXBUFFER_HPP
