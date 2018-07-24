//
// Created by FLXR on 7/23/2018.
//

#ifndef X808_GLFRAMEBUFFER_HPP
#define X808_GLFRAMEBUFFER_HPP


#include "gfx/api/framebuffer.hpp"
#include "math/vec4.hpp"
#include "gltexture2d.hpp"

namespace xe { namespace gfx { namespace api {

	class GLFrameBuffer : public FrameBuffer {
	public:
		explicit GLFrameBuffer(uint width, uint height, uint type);
		~GLFrameBuffer();

		void bind() override;
		void unbind() override;

		void clear() override;

		inline const Texture *getTexture() override { return texture; }

		inline uint getWidth() override { return width; }
		inline uint getHeight() override { return height; }

		inline void setClearColor(const vec4 &color) override {GLFrameBuffer::color = color;}

	private:
		uint frameBufferHandle;
		uint renderBufferHandle;
		GLTexture2D *texture;

		uint width;
		uint height;
		uint type;

		vec4 color;
	};

}}}


#endif //X808_GLFRAMEBUFFER_HPP