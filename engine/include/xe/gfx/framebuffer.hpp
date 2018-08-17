//
// Created by FLXR on 8/8/2018.
//

#ifndef X808_FRAMEBUFFER_HPP
#define X808_FRAMEBUFFER_HPP


#include <unordered_map>
#include <xe/gfx/texture.hpp>

namespace xe {

	namespace internal {
		class PlatformFrameBuffer;
	}

	class XE_API FrameBuffer {
	public:
		explicit FrameBuffer(const string &name);
		~FrameBuffer();

		void load(const std::unordered_map<Attachment, Texture *> &attachments);

		void bindDrawAttachment(Attachment attachment);
		void bindDrawAttachments(Attachment *attachments, uint size);
		void bindReadAttachment(Attachment attachment);

		void bindDraw(Attachment attachment);
		void bindDraw(Attachment *attachments, uint size);
		void bindRead(Attachment attachment);
		void unbind();

		void bindTexture(Attachment attachment, Texture *texture);

		uint getHandle() const;
		const string &getName();
		Texture *getTexture(Attachment attachment);

	private:
		internal::PlatformFrameBuffer *buffer;
	};

}


#endif //X808_FRAMEBUFFER_HPP
