//
// Created by FLXR on 7/3/2018.
//

#ifndef X808_TEXTUREMANAGER_HPP
#define X808_TEXTUREMANAGER_HPP


#include <unordered_map>
#include <xe/common.hpp>
#include <xe/utils/noncopyable.hpp>
#include <xe/gfx/texture.hpp>
#include <xe/utils/string.hpp>

namespace xe {

	class XE_API TextureManager : NonCopyable {
	public:
		~TextureManager() override;

		static void init();

		static bool add(Texture *texture);
		static const Texture *get(const string &name);

		static void clean();

	private:
		TextureManager();

		void createDefaultTextures();

		static TextureManager &instance();

	private:
		std::unordered_map<string, const Texture *> textures;
	};

}

#define GETTEXTURE(name) xe::TextureManager::get(name)


#endif //X808_TEXTUREMANAGER_HPP
