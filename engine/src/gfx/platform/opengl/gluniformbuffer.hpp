//
// Created by FLXR on 8/7/2018.
//

#ifndef X808_GLUNIFORMBUFFER_HPP
#define X808_GLUNIFORMBUFFER_HPP


#include <gfx/platform/platformuniformbuffer.hpp>
#include <xe/gfx/bufferlayout.hpp>

namespace xe { namespace internal {

	class GLUniformBuffer : public PlatformUniformBuffer {
	public:
		explicit GLUniformBuffer(BufferStorage storage, uint bind, const BufferLayout &layout, uint size);
		~GLUniformBuffer() override;

		void bind() override;
		void unbind() override;

		void update(const void *data, uint index, uint layoutIndex) override;

		inline uint getHandle() const override { return handle; }

	private:
		BufferLayout layout;
		uint handle;
	};

}}


#endif //X808_GLUNIFORMBUFFER_HPP
