//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_INDEXBUFFER_HPP
#define X808_INDEXBUFFER_HPP


#include "common.hpp"
#include "xeint.hpp"

namespace xe { namespace gfx { namespace api {

	class XE_API IndexBuffer {
	public:
		explicit IndexBuffer(uint16 *data, uint count);
		explicit IndexBuffer(uint *data, uint count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		inline uint getCount() const { return count; }

	private:
		uint handle;
		uint count;
	};


}}}

#endif //X808_INDEXBUFFER_HPP
