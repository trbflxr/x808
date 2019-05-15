//
// Created by FLXR on 9/1/2018.
//

#include <GL/glew.h>
#include "glcommon.hpp"
#include "glstoragebuffer.hpp"

namespace xe::internal {

  GLStorageBuffer::GLStorageBuffer(uint size) {

    glCall(glGenBuffers(1, &handle));

    glCall(glBindBuffer(GL_SHADER_STORAGE_BUFFER, handle));

    glCall(glBufferData(GL_SHADER_STORAGE_BUFFER, size, nullptr, GL_DYNAMIC_COPY));

    glCall(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));
  }

  GLStorageBuffer::~GLStorageBuffer() {
    glCall(glDeleteBuffers(1, &handle));
  }

  void GLStorageBuffer::update(const void *data, uint size) {
    glCall(glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_COPY));
  }

  void GLStorageBuffer::bind() const {
    glCall(glBindBuffer(GL_SHADER_STORAGE_BUFFER, handle));
  }

  void GLStorageBuffer::bind(uint index) const {
    glCall(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, handle));
  }

  void GLStorageBuffer::unbind() const {
    glCall(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));
  }

  void GLStorageBuffer::unbind(uint index) const {
    glCall(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, 0));
  }

}