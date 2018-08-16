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
		virtual ~IndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		inline uint getCount() const { return count; }

		static IndexBuffer *create(const uint16 *data, uint count);
		static IndexBuffer *create(const uint *data, uint count);

	protected:
		uint handle;
		uint count;
	};

}}

#endif //X808_INDEXBUFFER_HPP
