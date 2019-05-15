//
// Created by FLXR on 8/16/2018.
//

#ifndef X808_PLATFORMVERTEXBUFFER_HPP
#define X808_PLATFORMVERTEXBUFFER_HPP


#include <xe/gfx/vertexbuffer.hpp>
#include <xe/xeint.hpp>

namespace xe::internal {

  class PlatformVertexBuffer {
  public:
    virtual ~PlatformVertexBuffer() = default;

    virtual void resize(uint size) = 0;
    virtual void setLayout(const BufferLayout &layout) const = 0;
    virtual void setData(uint size, const void *data) const = 0;

    virtual void releasePointer() const = 0;
    virtual void *getPointer() const = 0;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
  };

}


#endif //X808_PLATFORMVERTEXBUFFER_HPP
