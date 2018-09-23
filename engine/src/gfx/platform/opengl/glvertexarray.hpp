//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLVERTEXARRAY_HPP
#define X808_GLVERTEXARRAY_HPP


#include <gfx/platform/platformvertexarray.hpp>

namespace xe { namespace internal {

	class GLVertexArray : public PlatformVertexArray {
	public:
		void bind() const override;
		void unbind() const override;

		void drawElements(uint count, BeginMode mode) const override;
		void drawArrays(uint count, BeginMode mode) const override;
		void drawArraysInstanced(uint count, uint instanceCount, BeginMode mode) const override;

		inline VertexBuffer *getBuffer(uint index) override { return buffers[index]; }
		inline void pushBuffer(VertexBuffer *buffer) override { buffers.push_back(buffer); }
		inline VertexBuffer *popBuffer() override {
			VertexBuffer *buffer = buffers.back();
			buffers.pop_back();
			return buffer;
		}

	private:
		std::vector<VertexBuffer *> buffers;
	};

}}


#endif //X808_GLVERTEXARRAY_HPP
