//
// Created by FLXR on 7/6/2018.
//

#include <GL/glew.h>
#include "glvertexbuffer.hpp"
#include "glcommon.hpp"
#include "glenums.hpp"

namespace xe::internal {

  GLVertexBuffer::GLVertexBuffer(BufferUsage usage) :
      usage(usage) {

    glCall(glGenBuffers(1, &handle));
  }

  GLVertexBuffer::~GLVertexBuffer() {
    glCall(glDeleteBuffers(1, &handle));
  }

  void GLVertexBuffer::resize(uint size) {
    GLVertexBuffer::size = size;

    bind();
    glCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, bufferUsageToGL(usage)));

    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
  }

  void GLVertexBuffer::setLayout(const BufferLayout &layout) const {
    GLVertexBuffer::layout = layout;
    const auto &l = layout.getLayout();

    for (uint i = 0; i < l.size(); i++) {
      auto &&element = l[i];
      glCall(glEnableVertexAttribArray(i));
      glCall(glVertexAttribPointer(i, element.count, element.type,
                                   static_cast<GLboolean>(element.normalized), layout.getStride(),
                                   reinterpret_cast<const void *> (element.offset)));
    }
  }

  void GLVertexBuffer::setData(uint size, const void *data) const {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, handle));
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, bufferUsageToGL(usage)));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
  }

  void GLVertexBuffer::releasePointer() const {
    glCall(glUnmapBuffer(GL_ARRAY_BUFFER));
  }

  void *GLVertexBuffer::getPointer() const {
    glCall(void *result = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    return result;
  }

  void GLVertexBuffer::bind() const {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, handle));
    setLayout(layout);
  }

  void GLVertexBuffer::unbind() const {
#ifdef XE_DEBUG
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
#endif
  }

}
