//
// Created by FLXR on 6/29/2018.
//

#include <xe/gfx/vertexbuffer.hpp>
#include <xe/gfx/context.hpp>
#include <gfx/platform/opengl/glvertexbuffer.hpp>
#include <xe/utils/logger.hpp>

namespace xe {

  VertexBuffer::VertexBuffer(BufferUsage usage) {
    switch (Context::getRenderAPI()) {
      case RenderAPI::OpenGL : {
        buffer = new internal::GLVertexBuffer(usage);
        break;
      }

      default: {
        XE_CORE_FATAL("[VertexBuffer]: selected render API is not supported");
        buffer = nullptr;
        break;
      }
    }
  }

  VertexBuffer::~VertexBuffer() {
    delete buffer;
  }

  void VertexBuffer::resize(uint size) {
    buffer->resize(size);
  }

  void VertexBuffer::setLayout(const BufferLayout &layout) const {
    buffer->setLayout(layout);
  }

  void VertexBuffer::setData(uint size, const void *data) const {
    buffer->setData(size, data);
  }

  void VertexBuffer::releasePointer() const {
    buffer->releasePointer();
  }

  void *VertexBuffer::getPointer() const {
    return buffer->getPointer();
  }

  void VertexBuffer::bind() const {
    buffer->bind();
  }

  void VertexBuffer::unbind() const {
    buffer->unbind();
  }

}