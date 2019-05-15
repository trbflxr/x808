//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_BUFFERLAYOUT_HPP
#define X808_BUFFERLAYOUT_HPP


#include <string>
#include <vector>
#include <xe/xeint.hpp>
#include <xe/math/math.hpp>
#include <xe/utils/assert.hpp>
#include <xe/gfx/context.hpp>
#include <xe/gfx/gltypes.hpp>

namespace xe {

  struct BufferElement {
    const char *name;
    uint type;
    uint size;
    uint count;
    uint offset;
    bool normalized;

    BufferElement(const char *name, uint type, uint size, uint count, uint offset, bool normalized) :
        name(name), type(type), size(size), count(count), offset(offset), normalized(normalized) { }
  };

  class BufferLayout {
  public:
    BufferLayout() : size(0) { }

    template<typename T>
    void push(const char *name, uint count = 1, bool normalized = false) {
      XE_ASSERT(false, "Unknown type!"); //for default types only
    }

    inline const std::vector<BufferElement> &getLayout() const { return layout; }
    inline uint getStride() const { return size; }

  private:
    void push(const char *name, uint type, uint size, uint count, bool normalized) {
      layout.emplace_back(name, type, size, count, BufferLayout::size, normalized);
      BufferLayout::size += size * count;
    }

  private:
    uint size;
    std::vector<BufferElement> layout;
  };

  template<>
  inline void BufferLayout::push<float>(const char *name, uint count, bool normalized) {
    switch (Context::getRenderAPI()) {
      case RenderAPI::OpenGL: push(name, GL_FLOAT, sizeof(float), count, normalized);
        break;

      default: break;
    }
  }

  template<>
  inline void BufferLayout::push<uint>(const char *name, uint count, bool normalized) {
    switch (Context::getRenderAPI()) {
      case RenderAPI::OpenGL: push(name, GL_UNSIGNED_INT, sizeof(uint), count, normalized);
        break;

      default: break;
    }
  }

  template<>
  inline void BufferLayout::push<int32>(const char *name, uint count, bool normalized) {
    switch (Context::getRenderAPI()) {
      case RenderAPI::OpenGL: push(name, GL_INT, sizeof(int32), count, normalized);
        break;

      default: break;
    }
  }

  template<>
  inline void BufferLayout::push<byte>(const char *name, uint count, bool normalized) {
    switch (Context::getRenderAPI()) {
      case RenderAPI::OpenGL: push(name, GL_UNSIGNED_BYTE, sizeof(byte), count, normalized);
        break;

      default: break;
    }
  }

  template<>
  inline void BufferLayout::push<vec2>(const char *name, uint count, bool normalized) {
    XE_ASSERT(count <= 1, "cant push more then 1 vec2");

    switch (Context::getRenderAPI()) {
      case RenderAPI::OpenGL: push(name, GL_FLOAT, sizeof(float), 2, normalized);
        break;

      default: break;
    }
  }

  template<>
  inline void BufferLayout::push<vec3>(const char *name, uint count, bool normalized) {
    XE_ASSERT(count <= 1, "cant push more then 1 vec3");

    switch (Context::getRenderAPI()) {
      case RenderAPI::OpenGL: push(name, GL_FLOAT, sizeof(float), 3, normalized);
        break;

      default: break;
    }
  }

  template<>
  inline void BufferLayout::push<vec4>(const char *name, uint count, bool normalized) {
    XE_ASSERT(count <= 1, "cant push more then 1 vec4");

    switch (Context::getRenderAPI()) {
      case RenderAPI::OpenGL: push(name, GL_FLOAT, sizeof(float), 4, normalized);
        break;

      default: break;
    }
  }

  template<>
  inline void BufferLayout::push<mat4>(const char *name, uint count, bool normalized) {
    XE_ASSERT(count <= 1, "cant push more then 1 mat4");

    switch (Context::getRenderAPI()) {
      case RenderAPI::OpenGL: push(name, GL_FLOAT, sizeof(float), 16, normalized);
        break;

      default: break;
    }
  }

}


#endif //X808_BUFFERLAYOUT_HPP
