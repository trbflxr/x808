//
// Created by FLXR on 6/30/2018.
//



#include <xe/gfx/texture.hpp>
#include <xe/gfx/context.hpp>
#include <xe/math/mathfunc.hpp>
#include <xe/utils/logger.hpp>

#include "gfx/platform/platformtexture.hpp"
#include "gfx/platform/opengl/gltexture.hpp"

namespace xe {

  Texture::Texture(const string &name, uint width, uint height, uint depth,
                   const TextureParameters &params, bool flip) :
      flipped(flip) {

    switch (Context::getRenderAPI()) {
      case RenderAPI::OpenGL: {
        texture = new internal::GLTexture(name, width, height, depth, params);
        break;
      }

      default: {
        XE_CORE_FATAL("[Texture]: selected render API is not supported");
        texture = nullptr;
        break;
      }
    }
  }

  Texture::Texture(const string &name, const string &path,
                   const TextureParameters &params, bool flip) :
      flipped(flip) {

    switch (Context::getRenderAPI()) {
      case RenderAPI::OpenGL: {
        texture = new internal::GLTexture(name, path, params);
        break;
      }

      default: {
        XE_CORE_FATAL("[Texture]: selected render API is not supported");
        texture = nullptr;
        break;
      }
    }
  }

  Texture::Texture(const string &name, byte *data, uint width, uint height,
                   const TextureParameters &params, bool flip) :
      flipped(flip) {

    switch (Context::getRenderAPI()) {
      case RenderAPI::OpenGL: {
        texture = new internal::GLTexture(name, data, width, height, params);
        break;
      }

      default: {
        XE_CORE_FATAL("[Texture]: selected render API is not supported");
        texture = nullptr;
        break;
      }
    }
  }

  Texture::~Texture() {
    delete texture;
  }

  void Texture::bind(uint slot) const {
    texture->bind(slot);
  }

  void Texture::bindImageUnit(uint index, TextureAccess access, uint level, uint layer) const {
    texture->bindImageUnit(index, access, level, layer);
  }

  void Texture::unbind(uint slot) const {
    texture->unbind(slot);
  }

  void Texture::setData2D(const void *pixels) const {
    texture->setData2D(pixels);
  }

  byte *Texture::getData2D() const {
    return texture->getData2D();
  }

  void Texture::generateMipMaps(const TextureTarget &target) {
    texture->generateMipMaps(target);
  }

  void Texture::copyTo(const Texture *texture) const {
    Texture::texture->copyTo(texture);
  }

  const string &Texture::getName() const {
    return texture->getName();
  }

  const string &Texture::getFilePath() const {
    return texture->getFilePath();
  }

  bool Texture::hasTransparency() const {
    return texture->hasTransparency();
  }

  uint Texture::getWidth() const {
    return texture->getWidth();
  }

  uint Texture::getHeight() const {
    return texture->getHeight();
  }

  uint Texture::getDepth() const {
    return texture->getDepth();
  }

  uint Texture::getHandle() const {
    return texture->getHandle();
  }

  TextureTarget Texture::getTarget() const {
    return texture->getTarget();
  }

  const TextureParameters &Texture::getParams() const {
    return texture->getParams();
  }

  uint Texture::getMaxMipMap() const {
    return getMaxMipMap(texture->getWidth(), texture->getHeight());
  }

  uint Texture::getMaxMipMap(uint width, uint height) {
    uint max = __max(width, height);
    return static_cast<uint>(math::logf(max, 2.0f) - 1.0f);
  }

}