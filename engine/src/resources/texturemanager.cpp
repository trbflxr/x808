//
// Created by FLXR on 7/3/2018.
//

#include "texturemanager.hpp"
#include "utils/log.hpp"
#include "gfx/api/texture.hpp"
#include "embedded/embedded.hpp"

namespace xe {

	TextureManager::TextureManager() {
		createDefaultTextures();
	}

	TextureManager::~TextureManager() {
		clean();
	}

	TextureManager &TextureManager::instance() {
		static TextureManager tm;
		return tm;
	}

	void TextureManager::add(api::Texture *texture) {
		auto &&it = instance().textures.find(texture->getName());

		if (it != instance().textures.end()) {
			XE_ERROR(texture->getName(), " already exist!");
			return;
		}

		instance().textures.emplace(texture->getName(), texture);
	}

	const api::Texture *TextureManager::get(const std::string_view &name) {
		auto &&it = instance().textures.find(name.data());
		if (it == instance().textures.end()) {
			XE_ERROR("Texture '", name, "' not found!");

			return get("default");
		}

		return it->second;
	}

	void TextureManager::clean() {
		instance().textures.clear();
	}

	void TextureManager::createDefaultTextures() {
		using namespace api;

		TextureParameters params(TextureTarget::TEX2D, TextureFilter::NEAREST);

		///texture
		Texture *errorTexture = Texture::create(internal::DEFAULT_TEXTURE_W,
		                                            internal::DEFAULT_TEXTURE_H, params);
		errorTexture->setData(internal::DEFAULT_TEXTURE);


		///normal
		Texture *defaultNormal = Texture::create(internal::DEFAULT_NORMAL_W,
		                                             internal::DEFAULT_NORMAL_H, params);
		defaultNormal->setData(internal::DEFAULT_NORMAL);


		///displacement map
		Texture *defaultDisp = Texture::create(internal::DEFAULT_DISP_W,
		                                           internal::DEFAULT_DISP_H, params);
		defaultDisp->setData(internal::DEFAULT_DISP);


		textures.emplace("normal", defaultNormal);
		textures.emplace("disp", defaultDisp);
		textures.emplace("default", errorTexture);
	}

}
