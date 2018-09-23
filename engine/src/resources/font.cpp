//
// Created by FLXR on 9/22/2018.
//

#include <xe/utils/log.hpp>
#include <xe/resources/font.hpp>
#include <xe/loaders/fontloader.hpp>

namespace xe {

	Font::Font(const string &name, const wstring &path) :
			name(name),
			path(path) {

		FontLoader loader(this);

		if (!loader.load()) {
			XE_ERROR("[Font]: failed to load font '", name, "'!");

			//todo: load default
		}
	}

	Font::~Font() {
		delete atlas;
	}

	const Glyph &Font::get(uint id) const {
		for (const auto &g : glyphs) {
			if (g.id == id) {
				return g;
			}
		}

		static Glyph nullGlyph{0};
		return nullGlyph;
	}

	float Font::getKerning(const Glyph &glyph, uint id) {
		for (const auto &k : glyph.kernings) {
			if (k.x == id) {
				return k.y;
			}
		}
		return 0.0f;
	}

}
