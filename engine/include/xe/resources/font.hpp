//
// Created by FLXR on 9/26/2018.
//

#ifndef X808_FONT_HPP
#define X808_FONT_HPP


#include <xe/xeint.hpp>
#include <xe/gfx/texture.hpp>

namespace xe {

	class XE_API Font {
	public:
		explicit Font(const string &name, const wstring &path, float size);
		explicit Font(const string &name, const byte *data, uint dataSize, float size, bool deleteData = true);
		~Font();

		inline const string &getName() const { return name; }
		inline const wstring &getPath() const { return path; }
		inline float getSize() const { return size; }

		const Texture *getTexture() const;

		void *getGlyph(wchar_t code) const;

		float getKerning(void *glyph, wchar_t c) const;

		void setOutlineThickness(float thickness) const;
		void setOutlineType(int32 type) const;

	private:
		void updateAtlas() const;

		void createAtlas(uint size);

		uint computeAtlasSize(float fontSize);

	private:
		friend struct FontLoader;

		string name;
		wstring path;
		float size;

		mutable Texture *texture;

		bool deleteFontData;
		byte *fontData;

		void *font;
		void *atlas;
	};

}


#endif //X808_FONTT_HPP
