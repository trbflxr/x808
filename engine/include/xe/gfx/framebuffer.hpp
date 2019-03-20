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

		void load(const std::unordered_map<Attachment, const Texture *> &attachments);

		void copy(FrameBuffer *dest);

		void bindDrawAttachment(Attachment attachment) const;
		void bindDrawAttachments(Attachment *attachments, uint size) const;
		void bindReadAttachment(Attachment attachment) const;

		void bindDraw(Attachment attachment) const;
		void bindDraw(Attachment *attachments, uint size) const;
		void bindRead(Attachment attachment) const;
		void unbind() const;

		void bindTexture(Attachment attachment, const Texture *texture) const;

		uint getHandle() const;
		const string &getName() const;
		const Texture *getTexture(Attachment attachment) const;

	private:
		internal::PlatformFrameBuffer *buffer;
	};

}


#endif //X808_FRAMEBUFFER_HPP
