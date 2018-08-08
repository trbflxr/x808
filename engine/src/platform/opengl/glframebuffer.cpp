//
// Created by FLXR on 8/8/2018.
//

#include "glcommon.hpp"
#include "glframebuffer.hpp"

namespace xe { namespace api {

	uint attachmentToGL(Attachment attachment) {
		switch (attachment) {
			case Attachment::COLOR0: return GL_COLOR_ATTACHMENT0;
			case Attachment::COLOR1: return GL_COLOR_ATTACHMENT1;
			case Attachment::COLOR2: return GL_COLOR_ATTACHMENT2;
			case Attachment::COLOR3: return GL_COLOR_ATTACHMENT3;
			case Attachment::COLOR4: return GL_COLOR_ATTACHMENT4;
			case Attachment::COLOR5: return GL_COLOR_ATTACHMENT5;
			case Attachment::COLOR6: return GL_COLOR_ATTACHMENT6;
			case Attachment::COLOR7: return GL_COLOR_ATTACHMENT7;
			case Attachment::COLOR8: return GL_COLOR_ATTACHMENT8;
			case Attachment::COLOR9: return GL_COLOR_ATTACHMENT9;
			case Attachment::COLOR10: return GL_COLOR_ATTACHMENT10;
			case Attachment::COLOR11: return GL_COLOR_ATTACHMENT11;
			case Attachment::COLOR12: return GL_COLOR_ATTACHMENT12;
			case Attachment::COLOR13: return GL_COLOR_ATTACHMENT13;
			case Attachment::COLOR14: return GL_COLOR_ATTACHMENT14;
			case Attachment::COLOR15: return GL_COLOR_ATTACHMENT15;
			case Attachment::DEPTH: return GL_DEPTH_ATTACHMENT;
			case Attachment::STENCIL: return GL_STENCIL_ATTACHMENT;
		}
	}

	GLFrameBuffer::GLFrameBuffer(const std::string_view &name) :
			FrameBuffer(name) {

		glCall(glGenFramebuffers(1, &handle));
	}

	GLFrameBuffer::~GLFrameBuffer() {
		glCall(glDeleteFramebuffers(1, &handle));
	}

	void GLFrameBuffer::load(const std::unordered_map<Attachment, api::Texture *> &attachments) {
		FrameBuffer::attachments = attachments;

		glCall(glBindFramebuffer(GL_FRAMEBUFFER, handle));

		for (auto &&a : attachments) {
			glCall(glFramebufferTexture(GL_FRAMEBUFFER, attachmentToGL(a.first), a.second->getHandle(), 0));
		}

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			XE_FATAL("[GLFrameBuffer]: creation fail");
			XE_ASSERT(false);
		}

		glCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void GLFrameBuffer::bindDrawAttachment(Attachment attachment) {
		glCall(glDrawBuffer(attachmentToGL(attachment)));
	}

	void GLFrameBuffer::bindDrawAttachments(Attachment *attachments, uint size) {
		uint buffers[size];
		for (uint i = 0; i < size; ++i) {
			buffers[i] = attachmentToGL(attachments[i]);
		}

		glCall(glDrawBuffers(size, buffers));
	}

	void GLFrameBuffer::bindReadAttachment(Attachment attachment) {
		uint mode = attachmentToGL(attachment);

		if (mode == GL_DEPTH_ATTACHMENT || mode == GL_STENCIL_ATTACHMENT) {
			XE_ERROR("[GLFrameBuffer]: Can't read depth or stencil attachments.");
			return;
		}

		glCall(glReadBuffer(mode));
	}

	void GLFrameBuffer::bindDraw(Attachment attachment) {
		glCall(glBindFramebuffer(GL_FRAMEBUFFER, handle));
		bindDrawAttachment(attachment);
	}

	void GLFrameBuffer::bindDraw(Attachment *attachments, uint size) {
		glCall(glBindFramebuffer(GL_FRAMEBUFFER, handle));
		bindDrawAttachments(attachments, size);
	}

	void GLFrameBuffer::bindRead(Attachment attachment) {
		glCall(glBindFramebuffer(GL_FRAMEBUFFER, handle));
		bindReadAttachment(attachment);
	}

	void GLFrameBuffer::unbind() {
		glCall(glDrawBuffer(0));
		glCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void GLFrameBuffer::bindTexture(Attachment attachment, api::Texture *texture) {
		glCall(glFramebufferTexture(GL_FRAMEBUFFER, attachmentToGL(attachment), texture->getHandle(), 0));

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			XE_FATAL("[GLFrameBuffer]: setting texture failed");
			XE_ASSERT(false);
		}
	}

}}
