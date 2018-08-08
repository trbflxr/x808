//
// Created by FLXR on 7/23/2018.
//

#ifndef X808_GLFRAMEBUFFEROLD_HPP
#define X808_GLFRAMEBUFFEROLD_HPP


#include "gfx/api/framebuffer_old.hpp"
#include "math/vec4.hpp"
#include "gltexture.hpp"

namespace xe { namespace api {

	class GLFrameBufferOld : public FrameBufferOld {
	public:
		explicit GLFrameBufferOld(uint width, uint height, Type type, TextureFilter filter);
		~GLFrameBufferOld();

		void bind() override;
		void unbind() override;

		void clear(uint buffer) override;

		inline const Texture *getTexture() const override { return texture; }
		inline Texture *getTexture() override { return texture; }

		inline uint getWidth() override { return width; }
		inline uint getHeight() override { return height; }

		inline void setClearColor(const vec4 &color) override;

	private:
		uint frameBufferHandle;
		uint renderBufferHandle;
		GLTexture *texture;

		uint width;
		uint height;
		Type type;
	};

}}


#endif //X808_GLFRAMEBUFFEROLD_HPP
