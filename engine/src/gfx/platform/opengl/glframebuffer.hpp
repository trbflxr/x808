//
// Created by FLXR on 8/8/2018.
//

#ifndef X808_GLFRAMEBUFFER_HPP
#define X808_GLFRAMEBUFFER_HPP


#include <gfx/platform/platformframebuffer.hpp>

namespace xe { namespace internal {

	class GLFrameBuffer : public PlatformFrameBuffer {
	public:
		explicit GLFrameBuffer(const std::string_view &name);
		~GLFrameBuffer() override;

		void load(const std::unordered_map<Attachment, const Texture *> &attachments) override;

		void bindDrawAttachment(Attachment attachment) const override;
		void bindDrawAttachments(Attachment *attachments, uint size) const override;
		void bindReadAttachment(Attachment attachment) const override;

		void bindDraw(Attachment attachment) const override;
		void bindDraw(Attachment *attachments, uint size) const override;
		void bindRead(Attachment attachment) const override;
		void unbind() override;

		void bindTexture(Attachment attachment, const Texture *texture) const override;

		inline uint getHandle() const override { return handle; }
		inline const string &getName() const override { return name; }
		inline const Texture *getTexture(Attachment attachment) override { return attachments[attachment]; }

	private:
		uint handle;
		string name;

		std::unordered_map<Attachment, const Texture *> attachments;
	};

}}


#endif //X808_GLFRAMEBUFFER_HPP
