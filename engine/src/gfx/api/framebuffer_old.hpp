//
// Created by FLXR on 7/23/2018.
//

#ifndef X808_FRAMEBUFFEROLD_HPP
#define X808_FRAMEBUFFEROLD_HPP


#include "xeint.hpp"
#include "texture.hpp"
#include "math/vec4.hpp"

namespace xe { namespace api {

	class XE_API FrameBufferOld {
	public:
		enum Type {
			COLOR = 0, DEPTH, RG32F
		};

	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void clear(uint buffer) = 0;

		virtual uint getWidth() = 0;
		virtual uint getHeight() = 0;

		virtual const Texture *getTexture() const = 0;
		virtual Texture *getTexture()  = 0;

		virtual void setClearColor(const vec4 &color) = 0;

		static FrameBufferOld *create(uint width, uint height, Type type,
		                           TextureMinFilter filter = TextureMinFilter::Nearest);

	protected:
		FrameBufferOld() = default;
	};

}}


#endif //X808_FRAMEBUFFEROLD_HPP
