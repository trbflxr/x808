//
// Created by FLXR on 8/8/2018.
//

#include <string>
#include <xe/xeint.hpp>
#include <xe/gfx/context.hpp>
#include <xe/utils/logger.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <gfx/platform/opengl/glframebuffer.hpp>

namespace xe {

	FrameBuffer::FrameBuffer(const string &name) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OpenGL : {
				buffer = new internal::GLFrameBuffer(name);
				break;
			}

			default: {
				XE_CORE_FATAL("[FrameBuffer]: selected render API is not supported");
				buffer = nullptr;
				break;
			}
		}
	}

	FrameBuffer::~FrameBuffer() {
		delete buffer;
	}

	void FrameBuffer::load(const std::unordered_map<Attachment, Texture *> &attachments) {
		buffer->load(attachments);
	}

	void FrameBuffer::bindDrawAttachment(Attachment attachment) const {
		buffer->bindDrawAttachment(attachment);
	}

	void FrameBuffer::bindDrawAttachments(Attachment *attachments, uint size) const {
		buffer->bindDrawAttachments(attachments, size);
	}

	void FrameBuffer::bindReadAttachment(Attachment attachment) const {
		buffer->bindReadAttachment(attachment);
	}

	void FrameBuffer::bindDraw(Attachment attachment) const {
		buffer->bindDraw(attachment);
	}

	void FrameBuffer::bindDraw(Attachment *attachments, uint size) const {
		buffer->bindDraw(attachments, size);
	}

	void FrameBuffer::bindRead(Attachment attachment) const {
		buffer->bindRead(attachment);
	}

	void FrameBuffer::unbind() const {
		buffer->unbind();
	}

	void FrameBuffer::bindTexture(Attachment attachment, Texture *texture) const {
		buffer->bindTexture(attachment, texture);
	}

	uint FrameBuffer::getHandle() const {
		return buffer->getHandle();
	}

	const string &FrameBuffer::getName() const {
		return buffer->getName();
	}

	Texture *FrameBuffer::getTexture(Attachment attachment) const {
		return buffer->getTexture(attachment);
	}

}
