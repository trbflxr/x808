//
// Created by FLXR on 8/8/2018.
//

#ifndef X808_GLFRAMEBUFFER_HPP
#define X808_GLFRAMEBUFFER_HPP


#include "gfx/api/framebuffer.hpp"

namespace xe { namespace api {

	class GLFrameBuffer : public FrameBuffer {
	public:
		explicit GLFrameBuffer(const std::string_view &name);
		~GLFrameBuffer();

		void load(const std::unordered_map<Attachment, api::Texture *> &attachments) override;

		void bindDrawAttachment(Attachment attachment) override;
		void bindDrawAttachments(Attachment *attachments, uint size) override;

		void bindReadAttachment(Attachment attachment) override;

		void bindDraw(Attachment attachment) override;
		void bindDraw(Attachment *attachments, uint size) override;

		void bindRead(Attachment attachment) override;

		void unbind() override;

		void bindTexture(Attachment attachment, api::Texture *texture) override;

		Texture *getTexture(Attachment attachment) override;
	};

}}


#endif //X808_GLFRAMEBUFFER_HPP
