//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_INDEXBUFFER_HPP
#define X808_INDEXBUFFER_HPP


#include "common.hpp"
#include "xeint.hpp"

namespace xe { namespace api {

	class XE_API IndexBuffer {
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint getCount() const = 0;

		static IndexBuffer *create(const uint16 *data, uint count);
		static IndexBuffer *create(const uint *data, uint count);
	};

}}

#endif //X808_INDEXBUFFER_HPP
