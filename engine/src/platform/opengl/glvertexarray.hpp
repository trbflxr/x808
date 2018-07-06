//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLVERTEXARRAY_HPP
#define X808_GLVERTEXARRAY_HPP


#include "gfx/api/vertexarray.hpp"

namespace xe { namespace gfx { namespace api {

	class GLVertexArray : public VertexArray {
	public:
		explicit GLVertexArray() = default;
		~GLVertexArray() = default;

		void bind() const override;
		void unbind() const override;

		void draw(uint count) const override;

		inline VertexBuffer *getBuffer(uint index) override { return buffers[index]; }
		void pushBuffer(VertexBuffer *buffer) override;

	private:
		uint handle;
		std::vector<api::VertexBuffer *> buffers;
	};

}}}


#endif //X808_GLVERTEXARRAY_HPP
