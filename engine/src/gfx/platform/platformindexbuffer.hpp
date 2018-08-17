//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_PLATFORMINDEXBUFFER_HPP
#define X808_PLATFORMINDEXBUFFER_HPP


#include <xe/xeint.hpp>

namespace xe { namespace internal {

	class PlatformIndexBuffer {
	public:
		virtual ~PlatformIndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint getCount() const = 0;
	};

}}

#endif //X808_PLATFORMINDEXBUFFER_HPP
