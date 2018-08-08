//
// Created by FLXR on 8/7/2018.
//

#ifndef X808_UNIFORMBUFFER_HPP
#define X808_UNIFORMBUFFER_HPP

#include "common.hpp"
#include "bufferlayout.hpp"

namespace xe { namespace api {

	class XE_API UniformBuffer {
	public:
		enum Storage {
			DYNAMIC, CLIENT
		};

	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void update(const void *data, uint index, uint layoutIndex = 0) = 0;

		virtual uint getHandle() const = 0;

		static UniformBuffer *create(Storage storage, uint bindIndex, const BufferLayout &layout, uint size = 1);
	};

}}


#endif //X808_UNIFORMBUFFER_HPP
