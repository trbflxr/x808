//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLVERTEXBUFFER_HPP
#define X808_GLVERTEXBUFFER_HPP


#include <gfx/platform/platformvertexbuffer.hpp>

namespace xe { namespace internal {

	class GLVertexBuffer : public PlatformVertexBuffer {
	public:
		explicit GLVertexBuffer(BufferUsage usage);
		~GLVertexBuffer() override;

		void resize(uint size) override;
		void setLayout(const BufferLayout &layout) override;
		void setData(uint size, const void *data) override;

		void releasePointer() override;
		void *getPointer() override;

		void bind() override;
		void unbind() override;

	private:
		uint handle;
		uint size;

		BufferUsage usage;
		BufferLayout layout;
	};

}}


#endif //X808_GLVERTEXBUFFER_HPP
