//
// Created by FLXR on 8/7/2018.
//

#ifndef X808_UNIFORMBUFFER_HPP
#define X808_UNIFORMBUFFER_HPP

#include <xe/common.hpp>
#include <xe/gfx/bufferlayout.hpp>
#include <xe/gfx/enums.hpp>

namespace xe {

  namespace internal {
    class PlatformUniformBuffer;
  }

  class XE_API UniformBuffer {
  public:
    explicit UniformBuffer(BufferStorage storage, uint bind, const BufferLayout &layout, uint size = 1);
    ~UniformBuffer();

    void bind();
    void unbind();

    void update(const void *data, uint index, uint layoutIndex = 0);

    uint getHandle() const;

  private:
    internal::PlatformUniformBuffer *buffer;
  };

}


#endif //X808_UNIFORMBUFFER_HPP
