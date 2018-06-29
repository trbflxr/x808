//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_VERTEXARRAY_HPP
#define X808_VERTEXARRAY_HPP


#include "vertexbuffer.hpp"

namespace xe { namespace gfx { namespace api {

	class XE_API VertexArray {
	public:
		void bind() const;
		void unbind() const;

		void draw(uint count) const;

		inline VertexBuffer *getBuffer(uint index = 0) { return buffers[index]; };
		void pushBuffer(VertexBuffer *buffer);

	private:
		std::vector<VertexBuffer *> buffers;
	};

}}}


#endif //X808_VERTEXARRAY_HPP
