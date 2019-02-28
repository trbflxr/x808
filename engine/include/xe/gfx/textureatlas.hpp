//
// Created by FLXR on 2/26/2019.
//

#ifndef X808_TEXTUREATLAS_HPP
#define X808_TEXTUREATLAS_HPP


#include <vector>
#include <xe/gfx/texture.hpp>
#include <xe/math/rect.hpp>

namespace xe {

	class XE_API TextureAtlas {
	public:
		explicit TextureAtlas(const string &name, const string &path, const TextureParameters &params);
		virtual ~TextureAtlas();

		const rect &getRect(const string &name) const;

		inline const string &getName() const { return texture->getName(); }
		inline const string &getPath() const { return path; }

		inline const Texture *getTexture() const { return texture; }

		inline const std::vector<std::pair<string, rect>> &getAreas() const { return areas; }

	private:
		string path;
		const Texture *texture;

		std::vector<std::pair<string, rect>> areas;
	};

}

#endif //X808_TEXTUREATLAS_HPP
