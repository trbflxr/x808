//
// Created by FLXR on 7/23/2018.
//

#ifndef X808_FRAMEBUFFER_HPP
#define X808_FRAMEBUFFER_HPP


#include "xeint.hpp"
#include "texture.hpp"
#include "math/vec4.hpp"

namespace xe { namespace gfx { namespace api {

	class XE_API FrameBuffer {
	public:
		enum {
			COLOR = 0, DEPTH
		};

	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void clear() = 0;

		virtual uint getWidth() = 0;
		virtual uint getHeight() = 0;

		virtual const Texture *getTexture() = 0;

		virtual void setClearColor(const vec4 &color) = 0;

		static FrameBuffer *create(uint width, uint height, uint type);

	protected:
		FrameBuffer() = default;
	};

}}}


#endif //X808_FRAMEBUFFER_HPP
