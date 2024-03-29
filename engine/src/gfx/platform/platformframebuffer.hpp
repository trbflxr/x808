//
// Created by FLXR on 8/8/2018.
//

#ifndef X808_PLATFORMFRAMEBUFFER_HPP
#define X808_PLATFORMFRAMEBUFFER_HPP


#include <unordered_map>
#include <xe/gfx/texture.hpp>

namespace xe::internal {

  class PlatformFrameBuffer {
  public:
    virtual ~PlatformFrameBuffer() = default;

    virtual void load(const std::unordered_map<Attachment, const Texture *> &attachments) = 0;

    virtual void copy(PlatformFrameBuffer *dest) = 0;

    virtual void bindDrawAttachment(Attachment attachment) const = 0;
    virtual void bindDrawAttachments(Attachment *attachments, uint size) const = 0;
    virtual void bindReadAttachment(Attachment attachment) const = 0;

    virtual void bindDraw(Attachment attachment) const = 0;
    virtual void bindDraw(Attachment *attachments, uint size) const = 0;
    virtual void bindRead(Attachment attachment) const = 0;
    virtual void unbind() const = 0;

    virtual void bindTexture(Attachment attachment, const Texture *texture) const = 0;

    virtual uint getHandle() const = 0;
    virtual const string &getName() const = 0;
    virtual const Texture *getTexture(Attachment attachment) = 0;
  };

}


#endif //X808_PLATFORMFRAMEBUFFER_HPP
