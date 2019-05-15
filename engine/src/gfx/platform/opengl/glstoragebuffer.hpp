//
// Created by FLXR on 9/1/2018.
//

#ifndef X808_GLSTORAGEBUFFER_HPP
#define X808_GLSTORAGEBUFFER_HPP


#include <gfx/platform/platformstoragebuffer.hpp>

namespace xe::internal {

  class GLStorageBuffer : public PlatformStorageBuffer {
  public:
    explicit GLStorageBuffer(uint size);
    ~GLStorageBuffer() override;

    void update(const void *data, uint size) override;

    void bind() const override;
    void bind(uint index) const override;

    void unbind() const override;
    void unbind(uint index) const override;

    inline uint getHandle() const override { return handle; }

  private:
    uint handle;
  };

}


#endif //X808_GLSTORAGEBUFFER_HPP
