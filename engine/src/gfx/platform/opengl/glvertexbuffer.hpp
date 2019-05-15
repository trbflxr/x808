//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLVERTEXBUFFER_HPP
#define X808_GLVERTEXBUFFER_HPP


#include <gfx/platform/platformvertexbuffer.hpp>

namespace xe::internal {

  class GLVertexBuffer : public PlatformVertexBuffer {
  public:
    explicit GLVertexBuffer(BufferUsage usage);
    ~GLVertexBuffer() override;

    void resize(uint size) override;
    void setLayout(const BufferLayout &layout) const override;
    void setData(uint size, const void *data) const override;

    void releasePointer() const override;
    void *getPointer() const override;

    void bind() const override;
    void unbind() const override;

  private:
    uint handle;
    uint size;

    BufferUsage usage;
    mutable BufferLayout layout;
  };

}


#endif //X808_GLVERTEXBUFFER_HPP
