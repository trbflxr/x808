//
// Created by FLXR on 8/8/2018.
//

#include <GL/glew.h>
#include "glcommon.hpp"
#include "glenums.hpp"
#include "glframebuffer.hpp"
#include <xe/utils/assert.hpp>

namespace xe { namespace internal {

	GLFrameBuffer::GLFrameBuffer(const std::string_view &name) :
			name(name) {

		glCall(glGenFramebuffers(1, &handle));
	}

	GLFrameBuffer::~GLFrameBuffer() {
		glCall(glDeleteFramebuffers(1, &handle));
	}

	void GLFrameBuffer::load(const std::unordered_map<Attachment, Texture *> &attachments) {
		GLFrameBuffer::attachments = attachments;

		glCall(glBindFramebuffer(GL_FRAMEBUFFER, handle));

		for (auto &&a : attachments) {
			glCall(glFramebufferTexture(GL_FRAMEBUFFER, attachmentToGL(a.first), a.second->getHandle(), 0));
		}

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			XE_CORE_FATAL("[GLFrameBuffer]: '", name,"' creation failed");
			XE_ASSERT(false);
		}

		glCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void GLFrameBuffer::bindDrawAttachment(Attachment attachment) const {
		glCall(glDrawBuffer(attachmentToGL(attachment)));
	}

	void GLFrameBuffer::bindDrawAttachments(Attachment *attachments, uint size) const {
		uint buffers[size];
		for (uint i = 0; i < size; ++i) {
			buffers[i] = attachmentToGL(attachments[i]);
		}

		glCall(glDrawBuffers(size, buffers));
	}

	void GLFrameBuffer::bindReadAttachment(Attachment attachment) const {
		uint mode = attachmentToGL(attachment);

		if (mode == GL_DEPTH_ATTACHMENT || mode == GL_STENCIL_ATTACHMENT) {
			XE_CORE_ERROR("[GLFrameBuffer]: Can't read depth or stencil attachments.");
			return;
		}

		glCall(glReadBuffer(mode));
	}

	void GLFrameBuffer::bindDraw(Attachment attachment) const {
		glCall(glBindFramebuffer(GL_FRAMEBUFFER, handle));
		bindDrawAttachment(attachment);
	}

	void GLFrameBuffer::bindDraw(Attachment *attachments, uint size) const {
		glCall(glBindFramebuffer(GL_FRAMEBUFFER, handle));
		bindDrawAttachments(attachments, size);
	}

	void GLFrameBuffer::bindRead(Attachment attachment) const {
		glCall(glBindFramebuffer(GL_FRAMEBUFFER, handle));
		bindReadAttachment(attachment);
	}

	void GLFrameBuffer::unbind() {
		glCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void GLFrameBuffer::bindTexture(Attachment attachment, Texture *texture) const {
		glCall(glFramebufferTexture(GL_FRAMEBUFFER, attachmentToGL(attachment), texture->getHandle(), 0));

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			XE_CORE_FATAL("[GLFrameBuffer]: setting texture failed");
			XE_ASSERT(false);
		}
	}

}}
