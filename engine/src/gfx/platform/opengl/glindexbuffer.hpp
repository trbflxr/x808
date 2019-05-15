//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLINDEXBUFFER_HPP
#define X808_GLINDEXBUFFER_HPP


#include <gfx/platform/platformindexbuffer.hpp>

namespace xe::internal {

  class GLIndexBuffer : public PlatformIndexBuffer {
  public:
    explicit GLIndexBuffer(const uint16 *data, uint count);
    explicit GLIndexBuffer(const uint *data, uint count);
    explicit GLIndexBuffer();
    ~GLIndexBuffer() override;

    void bind() const override;
    void unbind() const override;

    inline uint getCount() const override { return count; }

    void setData(const uint16 *data, uint count) override;
    void setData(const uint *data, uint count) override;

  private:
    uint handle;
    uint count;
  };

}

#endif //X808_GLINDEXBUFFER_HPP
