//
// Created by FLXR on 8/7/2018.
//

#ifndef X808_PLATFORMUNIFORMBUFFER_HPP
#define X808_PLATFORMUNIFORMBUFFER_HPP

#include <xe/xeint.hpp>
#include <xe/gfx/enums.hpp>

namespace xe::internal {

  class PlatformUniformBuffer {
  public:
    virtual ~PlatformUniformBuffer() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual void update(const void *data, uint index, uint layoutIndex) = 0;

    virtual uint getHandle() const = 0;
  };

}


#endif //X808_UNIFORMBUFFER_HPP
