//
// Created by FLXR on 7/3/2018.
//

#include <xe/resources/texturemanager.hpp>
#include <xe/utils/log.hpp>
#include <embedded/embedded.hpp>

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

	void TextureManager::add(Texture *texture, bool showWarn) {
		auto &&it = instance().textures.find(texture->getName());

		if (it != instance().textures.end()) {
			if (showWarn) {
				XE_ERROR(texture->getName(), " already exist!");
			}
			return;
		}

		instance().textures.emplace(texture->getName(), texture);
	}

	const Texture *TextureManager::get(const string &name) {
		auto &&it = instance().textures.find(name.data());
		if (it == instance().textures.end()) {
			XE_ERROR("Texture '", name, "' not found!");

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
		TextureParameters params(TextureTarget::Tex2D,
		                         PixelInternalFormat::Rgba,
		                         PixelFormat::Rgba,
		                         PixelType::UnsignedByte,
		                         TextureMinFilter::Nearest,
		                         TextureMagFilter::Nearest);

		///texture
		Texture *errorTexture = new Texture("default", internal::DEFAULT_TEXTURE_W,
		                                    internal::DEFAULT_TEXTURE_H, 0, params);
		errorTexture->setData2D(internal::DEFAULT_TEXTURE);

		//todo: remove

		///normal
		Texture *defaultNormal = new Texture("defaultNormal", internal::DEFAULT_NORMAL_W,
		                                     internal::DEFAULT_NORMAL_H, 0, params);
		defaultNormal->setData2D(internal::DEFAULT_NORMAL);


		///displacement map
		Texture *defaultDisp = new Texture("defaultDispMap", internal::DEFAULT_DISP_W,
		                                   internal::DEFAULT_DISP_H, 0, params);
		defaultDisp->setData2D(internal::DEFAULT_DISP);


		textures.emplace("normal", defaultNormal);
		textures.emplace("disp", defaultDisp);
		textures.emplace("default", errorTexture);
	}

}
