//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLINDEXBUFFER_HPP
#define X808_GLINDEXBUFFER_HPP


#include "gfx/api/indexbuffer.hpp"

namespace xe { namespace gfx { namespace api {

	class GLIndexBuffer : public IndexBuffer {
	public:
		explicit GLIndexBuffer(uint16 *data, uint count);
		explicit GLIndexBuffer(uint *data, uint count);
		~GLIndexBuffer();

		void bind() const override;
		void unbind() const override;

		inline uint getCount() const override { return count;}

	private:
		uint handle;
		uint count;
	};


}}}

#endif //X808_GLINDEXBUFFER_HPP
