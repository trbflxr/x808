//
// Created by FLXR on 9/1/2018.
//

#ifndef X808_PLATFORMSTORAGEBUFFER_HPP
#define X808_PLATFORMSTORAGEBUFFER_HPP


#include <xe/gfx/bufferlayout.hpp>

namespace xe { namespace internal {

	class PlatformStorageBuffer {
	public:
		virtual ~PlatformStorageBuffer() = default;

		virtual void update(const void *data, uint size) = 0;

		virtual void bind() const = 0;
		virtual void bind(uint index) const = 0;

		virtual void unbind() const = 0;
		virtual void unbind(uint index) const = 0;

		virtual uint getHandle() const = 0;
	};

}}


#endif //X808_PLATFORMSTORAGEBUFFER_HPP
