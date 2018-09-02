//
// Created by FLXR on 9/1/2018.
//

#ifndef X808_STORAGEBUFFER_HPP
#define X808_STORAGEBUFFER_HPP


#include <xe/common.hpp>
#include <xe/gfx/bufferlayout.hpp>

namespace xe {

	namespace internal {
		class PlatformStorageBuffer;
	}

	class XE_API StorageBuffer {
	public:
		explicit StorageBuffer(uint size);
		~StorageBuffer();

		void update(const void *data, uint size);

		void bind();
		void bind(uint index);

		void unbind();
		void unbind(uint index);

		uint getHandle();

	private:
		internal::PlatformStorageBuffer *buffer;
	};

}


#endif //X808_STORAGEBUFFER_HPP
