//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLVERTEXARRAY_HPP
#define X808_GLVERTEXARRAY_HPP


#include "gfx/api/vertexarray.hpp"

namespace xe { namespace api {

	class GLVertexArray : public VertexArray {
	public:
		void bind() const override;
		void unbind() const override;

		void drawElements(uint count, BeginMode mode) const override;
		void drawArrays(uint count, BeginMode mode) const override;
		void drawArraysInstanced(uint count, uint instanceCount, BeginMode mode) const override;
	};

}}


#endif //X808_GLVERTEXARRAY_HPP
