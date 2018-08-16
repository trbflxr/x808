//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLINDEXBUFFER_HPP
#define X808_GLINDEXBUFFER_HPP


#include "gfx/api/indexbuffer.hpp"

namespace xe { namespace api {

	class GLIndexBuffer : public IndexBuffer {
	public:
		explicit GLIndexBuffer(const uint16 *data, uint count);
		explicit GLIndexBuffer(const uint *data, uint count);
		~GLIndexBuffer() override;

		void bind() const override;
		void unbind() const override;
	};

}}

#endif //X808_GLINDEXBUFFER_HPP
