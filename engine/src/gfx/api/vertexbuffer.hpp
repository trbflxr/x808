//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_VERTEXBUFFER_HPP
#define X808_VERTEXBUFFER_HPP


#include "common.hpp"
#include "enums.hpp"
#include "bufferlayout.hpp"

namespace xe { namespace api {

	class XE_API VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void resize(uint size) = 0;
		virtual void setLayout(const BufferLayout &layout) = 0;
		virtual void setData(uint size, const void *data) = 0;

		virtual void releasePointer() = 0;

		virtual void bind() = 0;
		virtual void unbind() = 0;

		template<typename T>
		T *getPointer() { return (T *) getPointerInternal(); }

		static VertexBuffer *create(BufferUsage usage = BufferUsage::StaticDraw);

	protected:
		VertexBuffer() = default;

		virtual void *getPointerInternal() = 0;

	};

}}


#endif //X808_VERTEXBUFFER_HPP
