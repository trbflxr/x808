//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_INDEXBUFFER_HPP
#define X808_INDEXBUFFER_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>

namespace xe {

	namespace internal {
		class PlatformIndexBuffer;
	}

	class XE_API IndexBuffer {
	public:
		explicit IndexBuffer(const uint16 *data, uint count);
		explicit IndexBuffer(const uint *data, uint count);
		~IndexBuffer();

		virtual void bind() const;
		virtual void unbind() const;

		virtual uint getCount() const;

	private:
		internal::PlatformIndexBuffer *buffer;
	};

}

#endif //X808_INDEXBUFFER_HPP
