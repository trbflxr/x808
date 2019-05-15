//
// Created by FLXR on 7/3/2018.
//

#include <xe/resources/texturemanager.hpp>
#include <xe/utils/logger.hpp>
#include <embedded/embedded.hpp>

namespace xe {

  TextureManager::TextureManager() {
    createDefaultTextures();
  }

  TextureManager::~TextureManager() {
    clean();
  }

  void TextureManager::init() {
    instance();
  }

  TextureManager &TextureManager::instance() {
    static TextureManager tm;
    return tm;
  }

  bool TextureManager::add(Texture *texture) {
    auto &&it = instance().textures.find(texture->getName());

    if (it != instance().textures.end()) {
      XE_CORE_ERROR("[TextureManager]: texture '", texture->getName(), "' already exist and be deleted");

      delete texture;
      return false;
    }

    instance().textures.emplace(texture->getName(), texture);

    return true;
  }

  bool TextureManager::add(TextureAtlas *atlas) {
    auto &&it = instance().atlases.find(atlas->getName());

    if (it != instance().atlases.end()) {
      XE_CORE_ERROR("[TextureManager]: atlas '", atlas->getName(), "' already exist and be deleted");

      delete atlas;
      return false;
    }

    instance().atlases.emplace(atlas->getName(), atlas);

    return true;
  }

  const Texture *TextureManager::get(const string &name) {
    auto &&it = instance().textures.find(name);
    if (it == instance().textures.end()) {
      XE_CORE_ERROR("[TextureManager]: texture '", name, "' not found!");

      return get("default");
    }

    return it->second;
  }

  const TextureAtlas *TextureManager::getAtlas(const string &name) {
    auto &&it = instance().atlases.find(name);
    if (it == instance().atlases.end()) {
      XE_CORE_ERROR("[TextureManager]: atlas '", name, "' not found!");

      return getAtlas("default");
    }

    return it->second;
  }

  void TextureManager::clean() {
    for (auto &&texture : instance().textures) {
      delete texture.second;
    }
  }

  void TextureManager::createDefaultTextures() {
    TextureParameters params(TextureTarget::Tex2D,
                             PixelInternalFormat::Rgba,
                             PixelFormat::Rgba,
                             PixelType::UnsignedByte,
                             TextureMinFilter::Linear,
                             TextureMagFilter::Linear);

    const Texture *errorTexture = new Texture("default", internal::DEFAULT_TEXTURE_W,
                                              internal::DEFAULT_TEXTURE_H, 0, params);
    errorTexture->setData2D(internal::DEFAULT_TEXTURE);

    textures.emplace("default", errorTexture);

    //error atlas
    const rect e = rect(0, 0, errorTexture->getWidth(), errorTexture->getHeight());
    TextureAtlas *ea = new TextureAtlas(errorTexture, {std::make_pair("error", e)});

    atlases.emplace("default", ea);

    //default textures
    params.minFilter = TextureMinFilter::Nearest;
    params.magFilter = TextureMagFilter::Nearest;
    params.mipMapLevels = 0;
    params.anisotropy = 0;

    const byte normalData[] = {128, 127, 255, 255};
    const byte specularData[] = {255, 255, 255, 255};

    const Texture *normal = new Texture("defaultNormal", 1, 1, 0, params);
    normal->setData2D(normalData);
    textures.emplace("defaultNormal", normal);

    const Texture *specular = new Texture("defaultSpecular", 1, 1, 0, params);
    specular->setData2D(specularData);
    textures.emplace("defaultSpecular", specular);
  }

}
