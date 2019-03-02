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
		enum class RenderMode {
			Normal, OutlineEdge, SignedDistanceField
		};

	public:
		explicit Font(const string &name, const string &path, float size);
		explicit Font(const string &name, const byte *data, uint dataSize, float size, bool deleteData = true);
		~Font();

		inline const string &getName() const { return name; }
		inline const string &getPath() const { return path; }
		inline float getSize() const { return size; }

		const Texture *getTexture() const;

		void *getGlyph(const char *code) const;

		float getKerning(void *glyph, const char *c) const;

		void setOutlineThickness(float thickness) const;

		void setRenderMode(RenderMode mode) const;

	private:
		void updateAtlas() const;

		void createAtlas(uint size);

		uint computeAtlasSize(float fontSize);

	private:
		friend class FontLoader;

		string name;
		string path;
		float size;

		mutable Texture *texture;

		bool deleteFontData;
		byte *fontData;

		void *font;
		void *atlas;
	};

}


#endif //X808_FONTT_HPP
