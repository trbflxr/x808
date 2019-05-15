//
// Created by FLXR on 8/8/2018.
//

#include <GL/glew.h>
#include "glcommon.hpp"
#include "glenums.hpp"
#include "glframebuffer.hpp"
#include <xe/utils/assert.hpp>

namespace xe::internal {

  GLFrameBuffer::GLFrameBuffer(const std::string_view &name) :
      name(name) {

    glCall(glGenFramebuffers(1, &handle));
  }

  GLFrameBuffer::~GLFrameBuffer() {
    glCall(glDeleteFramebuffers(1, &handle));
  }

  void GLFrameBuffer::load(const std::unordered_map<Attachment, const Texture *> &attachments) {
    GLFrameBuffer::attachments = attachments;

    glCall(glBindFramebuffer(GL_FRAMEBUFFER, handle));

    for (auto &&a : attachments) {
      glCall(glFramebufferTexture(GL_FRAMEBUFFER, attachmentToGL(a.first), a.second->getHandle(), 0));
    }

    glCall(uint result = glCheckFramebufferStatus(GL_FRAMEBUFFER));
    if (result != GL_FRAMEBUFFER_COMPLETE) {
      XE_CORE_FATAL("[GLFrameBuffer]: '", name, "' creation failed, code: ", result);
      XE_ASSERT(false);
    }

    glCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
  }

  void GLFrameBuffer::copy(PlatformFrameBuffer *dest) {
    const GLFrameBuffer *other = dynamic_cast<const GLFrameBuffer *>(dest);

    if (attachments.size() != other->attachments.size()) {
      XE_CORE_ERROR("[GLFrameBuffer]: Unable to copy framebuffer. Attachments count have to be same.");
      return;
    }

    for (const auto &a : attachments) {
      if (a.first == Attachment::None)continue;

#ifdef XE_DEBUG
      auto &&it = other->attachments.find(a.first);
      if (it == other->attachments.end()) {
        XE_CORE_ERROR(
            "[GLFrameBuffer]: Unable to copy framebuffer. Buffer attachments have to be same.");
        XE_ASSERT(false);
      }
#endif

      const uint size = a.second->getWidth();
      uint mode = 0;

      if (a.first == Attachment::Depth) {
        mode = GL_DEPTH_BUFFER_BIT;
      } else if (a.first == Attachment::Stencil) {
        mode = GL_STENCIL_BUFFER_BIT;
      } else if (a.first == Attachment::DepthStencil) {
        mode = GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
      }

      if (mode == 0) {
        const uint attachment = attachmentToGL(a.first);
        glCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, handle));
        glCall(glReadBuffer(attachment));
        glCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, other->handle));
        glCall(glDrawBuffer(attachment));

        glCall(glBlitFramebuffer(0, 0, size, size, 0, 0, size, size, GL_COLOR_BUFFER_BIT, GL_NEAREST));
      } else {
        glCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, handle));
        glCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, other->handle));
        glCall(glBlitFramebuffer(0, 0, size, size, 0, 0, size, size, mode, GL_NEAREST));
      }
    }

    glCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));
    glCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));

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

    if (mode == GL_DEPTH_ATTACHMENT || mode == GL_STENCIL_ATTACHMENT || mode == GL_DEPTH_STENCIL_ATTACHMENT) {
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

  void GLFrameBuffer::unbind() const {
    glCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
  }

  void GLFrameBuffer::bindTexture(Attachment attachment, const Texture *texture) const {
    glCall(glFramebufferTexture(GL_FRAMEBUFFER, attachmentToGL(attachment), texture->getHandle(), 0));

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      XE_CORE_FATAL("[GLFrameBuffer]: setting texture failed");
      XE_ASSERT(false);
    }
  }

}
