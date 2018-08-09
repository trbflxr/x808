//
// Created by FLXR on 8/8/2018.
//

#ifndef X808_FRAMEBUFFER_HPP
#define X808_FRAMEBUFFER_HPP


#include <unordered_map>
#include "texture.hpp"

namespace xe { namespace api {

	class XE_API FrameBuffer {
	public:
		inline uint getHandle() const { return handle; }
		inline const std::string &getName() const { return name; }

		virtual void load(const std::unordered_map<Attachment, api::Texture *> &attachments) = 0;

		virtual void bindDrawAttachment(Attachment attachment) = 0;
		virtual void bindDrawAttachments(Attachment *attachments, uint size) = 0;

		virtual void bindReadAttachment(Attachment attachment) = 0;

		virtual void bindDraw(Attachment attachment) = 0;
		virtual void bindDraw(Attachment *attachments, uint size) = 0;

		virtual void bindRead(Attachment attachment) = 0;

		virtual void unbind() = 0;

		virtual void bindTexture(Attachment attachment, api::Texture *texture) = 0;

		static FrameBuffer *create(const std::string_view &name);

	protected:
		explicit FrameBuffer(const std::string_view &name);

	protected:
		uint handle;
		std::string name;

		std::unordered_map<Attachment, api::Texture *> attachments;
	};

}}


#endif //X808_FRAMEBUFFER_HPP
