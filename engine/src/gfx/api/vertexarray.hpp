//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_VERTEXARRAY_HPP
#define X808_VERTEXARRAY_HPP


#include "vertexbuffer.hpp"

namespace xe { namespace api {

	class XE_API VertexArray {
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void draw(uint count) const = 0;

		virtual VertexBuffer *getBuffer(uint index) = 0;
		virtual void pushBuffer(VertexBuffer *buffer) = 0;

		static VertexArray* create();
	};

}}


#endif //X808_VERTEXARRAY_HPP
