//
// Created by FLXR on 7/23/2018.
//

#include "glframebuffer.hpp"
#include "glcommon.hpp"
#include "gfx/renderer.hpp"

namespace xe { namespace api {

	uint rendererBufferToGL(uint buffer) {
		uint result = 0;

		if (buffer & RENDERER_BUFFER_COLOR) {
			result |= GL_COLOR_BUFFER_BIT;
		}
		if (buffer & RENDERER_BUFFER_DEPTH) {
			result |= GL_DEPTH_BUFFER_BIT;
		}
		if (buffer & RENDERER_BUFFER_STENCIL) {
			result |= GL_STENCIL_BUFFER_BIT;
		}
		return result;
	}

	GLFrameBuffer::GLFrameBuffer(uint width, uint height, Type type, TextureFilter filter) :
			width(width),
			height(height),
			type(type),
			frameBufferHandle(0),
			renderBufferHandle(0) {

		if (type == FrameBuffer::DEPTH) {
			glCall(glGenFramebuffers(1, &frameBufferHandle));
			glCall(glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle));

			TextureParameters params(TextureTarget::TEX2D, TextureFormat::DEPTH16, filter, TextureWrap::CLAMP);
			texture = new GLTexture(width, height, params);

			glCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture->getHandle(), 0));
			glCall(glDrawBuffer(GL_NONE));

		} else {
			auto format = type == FrameBuffer::RG32F ? TextureFormat::RG32F : TextureFormat::RGBA;

			TextureParameters params(TextureTarget::TEX2D, format, filter, TextureWrap::CLAMP);
			texture = new GLTexture(width, height, params);

			glCall(glGenFramebuffers(1, &frameBufferHandle));
			glCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferHandle));

			glCall(glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			                              GL_TEXTURE_2D, texture->getHandle(), 0));

			glCall(glGenRenderbuffers(1, &renderBufferHandle));
			glCall(glBindRenderbuffer(GL_RENDERBUFFER, renderBufferHandle));
			glCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height));

			glCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			                                 GL_RENDERBUFFER, renderBufferHandle));

			glCall(glDrawBuffer(GL_COLOR_ATTACHMENT0));
		}

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			XE_FATAL("[GLFrameBuffer2D]: creation fail");
			XE_ASSERT(false);
		}

		glCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	GLFrameBuffer::~GLFrameBuffer() {
		delete texture;

		if (frameBufferHandle) {
			glCall(glDeleteFramebuffers(1, &frameBufferHandle));
		}

		if (renderBufferHandle) {
			glCall(glDeleteRenderbuffers(1, &renderBufferHandle));
		}
	}

	void GLFrameBuffer::bind() {
		glCall(glBindTexture(GL_TEXTURE_2D, 0));
		glCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferHandle));
		glCall(glViewport(0, 0, width, height));
	}

	void GLFrameBuffer::unbind() {
		glCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
	}

	void GLFrameBuffer::clear(uint buffer) {
		glCall(glClear(rendererBufferToGL(buffer)));
	}

	void GLFrameBuffer::setClearColor(const vec4 &color) {
		glCall(glClearColor(color.x, color.y, color.z, color.w));
	}

}}