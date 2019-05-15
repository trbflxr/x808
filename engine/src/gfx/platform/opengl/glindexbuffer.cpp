//
// Created by FLXR on 7/6/2018.
//

#include <GL/glew.h>
#include "glcommon.hpp"
#include "glindexbuffer.hpp"

namespace xe::internal {

  GLIndexBuffer::GLIndexBuffer(const uint16 *data, uint count) :
      count(count) {

    glCall(glGenBuffers(1, &handle));
    setData(data, count);
  }

  GLIndexBuffer::GLIndexBuffer(const uint *data, uint count) :
      count(count) {

    glCall(glGenBuffers(1, &handle));
    setData(data, count);
  }

  GLIndexBuffer::GLIndexBuffer() {
    glCall(glGenBuffers(1, &handle));
  }

  GLIndexBuffer::~GLIndexBuffer() {
    glCall(glDeleteBuffers(1, &handle));
  }

  void GLIndexBuffer::bind() const {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
  }

  void GLIndexBuffer::unbind() const {
#ifdef XE_DEBUG
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
#endif
  }

  void GLIndexBuffer::setData(const uint16 *data, uint count) {
    GLIndexBuffer::count = count;

    bind();
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint16), data, GL_STATIC_DRAW));

    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
  }

  void GLIndexBuffer::setData(const uint *data, uint count) {
    GLIndexBuffer::count = count;

    bind();
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));

    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
  }

}