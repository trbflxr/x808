//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLVERTEXBUFFER_HPP
#define X808_GLVERTEXBUFFER_HPP


#include "gfx/api/vertexbuffer.hpp"

namespace xe{namespace gfx{namespace api{

	class XE_API GLVertexBuffer : public VertexBuffer{
	public:
		explicit GLVertexBuffer(BufferType type);
		~GLVertexBuffer() override;

		void resize(uint size) override;
		void setLayout(const BufferLayout &layout) override;
		void setData(uint size, const void *data) override;

		void releasePointer() override;

		void bind() override;
		void unbind() override;

	protected:
		void *getPointerInternal() override;

	private:
		uint handle;
		uint size;
		BufferType type;
		BufferLayout layout;
	};

}}}


#endif //X808_GLVERTEXBUFFER_HPP
