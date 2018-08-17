//
// Created by FLXR on 8/8/2018.
//

#include <string_view>
#include <xe/xeint.hpp>
#include <xe/gfx/context.hpp>
#include <xe/utils/log.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <gfx/platform/opengl/glframebuffer.hpp>

namespace xe {

	FrameBuffer::FrameBuffer(const string &name) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : {
				buffer = new internal::GLFrameBuffer(name);
				break;
			}

			default: {
				XE_FATAL("[FrameBuffer]: selected render API is not supported");
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

	void FrameBuffer::bindDrawAttachment(Attachment attachment) {
		buffer->bindDrawAttachment(attachment);
	}

	void FrameBuffer::bindDrawAttachments(Attachment *attachments, uint size) {
		buffer->bindDrawAttachments(attachments, size);
	}

	void FrameBuffer::bindReadAttachment(Attachment attachment) {
		buffer->bindReadAttachment(attachment);
	}

	void FrameBuffer::bindDraw(Attachment attachment) {
		buffer->bindDraw(attachment);
	}

	void FrameBuffer::bindDraw(Attachment *attachments, uint size) {
		buffer->bindDraw(attachments, size);
	}

	void FrameBuffer::bindRead(Attachment attachment) {
		buffer->bindRead(attachment);
	}

	void FrameBuffer::unbind() {
		buffer->unbind();
	}

	void FrameBuffer::bindTexture(Attachment attachment, Texture *texture) {
		buffer->bindTexture(attachment, texture);
	}

	uint FrameBuffer::getHandle() const {
		return buffer->getHandle();
	}

	const string &FrameBuffer::getName() {
		return buffer->getName();
	}

	Texture *FrameBuffer::getTexture(Attachment attachment) {
		return buffer->getTexture(attachment);
	}

}
