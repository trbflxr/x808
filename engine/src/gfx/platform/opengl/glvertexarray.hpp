//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLVERTEXARRAY_HPP
#define X808_GLVERTEXARRAY_HPP


#include <gfx/platform/platformvertexarray.hpp>

namespace xe { namespace internal {

	class GLVertexArray : public PlatformVertexArray {
	public:
		~GLVertexArray() override;

		void bind() const override;
		void unbind() const override;

		void drawElements(uint count, BeginMode mode, const void *indices) const override;
		void drawElementsInstanced(uint count, BeginMode mode, uint instances, const void *indices) const override;
		void drawArrays(uint count, BeginMode mode) const override;
		void drawArraysInstanced(uint count, uint instanceCount, BeginMode mode) const override;

		inline VertexBuffer *getBuffer(uint index) override { return buffers[index]; }
		inline void pushBuffer(VertexBuffer *buffer) override { buffers.push_back(buffer); }

	private:
		std::vector<VertexBuffer *> buffers;
	};

}}


#endif //X808_GLVERTEXARRAY_HPP
