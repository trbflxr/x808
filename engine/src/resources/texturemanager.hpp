//
// Created by FLXR on 7/3/2018.
//

#ifndef X808_TEXTUREMANAGER_HPP
#define X808_TEXTUREMANAGER_HPP


#include <unordered_map>
#include "common.hpp"
#include "gfx/api/texture.hpp"

namespace xe {

	class XE_API TextureManager {
	public:
		~TextureManager();

		static void add(gfx::api::Texture *texture);
		static const gfx::api::Texture &get(const std::string_view &name);

		static void clean();

		NULL_COPY_AND_ASSIGN(TextureManager);

	private:
		TextureManager();

		static TextureManager &instance();

	private:
		std::unordered_map<std::string, gfx::api::Texture *> textures;
	};

}

#define GETTEXTURE(name) xe::TextureManager::get(name)


#endif //X808_TEXTUREMANAGER_HPP
