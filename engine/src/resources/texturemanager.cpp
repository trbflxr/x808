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

	const Texture *TextureManager::get(const string &name) {
		auto &&it = instance().textures.find(name);
		if (it == instance().textures.end()) {
			XE_CORE_ERROR("[TextureManager]: texture '", name, "' not found!");

			return get("default");
		}

		return it->second;
	}

	void TextureManager::clean() {
		for (auto &&texture : instance().textures) {
			delete texture.second;
		}
	}

	void TextureManager::createDefaultTextures() {
		static TextureParameters params(TextureTarget::Tex2D,
		                                PixelInternalFormat::Rgb,
		                                PixelFormat::Rgb,
		                                PixelType::UnsignedByte,
		                                TextureMinFilter::Linear,
		                                TextureMagFilter::Linear);

		Texture *errorTexture = new Texture("default", internal::DEFAULT_TEXTURE_W,
		                                    internal::DEFAULT_TEXTURE_H, 0, params);
		errorTexture->setData2D(internal::DEFAULT_TEXTURE);

		textures.emplace("default", errorTexture);
	}

}
