//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_PLATFORMINDEXBUFFER_HPP
#define X808_PLATFORMINDEXBUFFER_HPP


#include <xe/xeint.hpp>

namespace xe::internal {

  class PlatformIndexBuffer {
  public:
    virtual ~PlatformIndexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual uint getCount() const = 0;

    virtual void setData(const uint16 *data, uint count) = 0;
    virtual void setData(const uint *data, uint count) = 0;
  };

}

#endif //X808_PLATFORMINDEXBUFFER_HPP
