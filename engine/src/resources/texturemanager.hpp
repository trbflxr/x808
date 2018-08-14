//
// Created by FLXR on 7/3/2018.
//

#ifndef X808_TEXTUREMANAGER_HPP
#define X808_TEXTUREMANAGER_HPP


#include <unordered_map>
#include "common.hpp"
#include "utils/noncopyable.hpp"
#include "gfx/api/texture.hpp"

namespace xe {

	class XE_API TextureManager : NonCopyable {
	public:
		~TextureManager() override;

		static void add(api::Texture *texture, bool showWarn = true);
		static const api::Texture *get(const std::string_view &name);

		static void clean();

	private:
		TextureManager();

		void createDefaultTextures();

		static TextureManager &instance();

	private:
		std::unordered_map<std::string, api::Texture *> textures;
	};

}

#define GETTEXTURE(name) xe::TextureManager::get(name)


#endif //X808_TEXTUREMANAGER_HPP
