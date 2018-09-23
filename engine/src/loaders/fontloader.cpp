//
// Created by FLXR on 9/22/2018.
//

#include <fstream>
#include <xe/utils/log.hpp>
#include <xe/loaders/fontloader.hpp>
#include <embedded/embedded.hpp>

namespace xe {

#define SPLITTER ' '
#define EQUAL_SPLITTER '='
#define NUMBER_SEPARATOR ','

#define PAD_TOP    0
#define PAD_LEFT   1
#define PAD_BOTTOM 2
#define PAD_RIGHT  3

	FontLoader::FontLoader(Font *font) :
			font(font) { }

	FontLoader::FontLoader(const string &name) {
		font = new Font();
		font->name = name;
		font->path = L"defaultFont";
	}

	int32 FontLoader::get(const string &key) {
		return atoi(values[key].c_str());
	}

	bool FontLoader::load(bool fromFile) {
		if (fromFile) {
			if (!readFile()) return false;
		} else {
			loadEmbed();
		}

		auto line = lines.begin();

		//parse padding
		parsePadding(*line++);

		//get atlas size
		parseLine(*line++);
		atlasSize = get("scaleW");
		values.clear();

		//load texture
		if (fromFile) {
			loadAtlas(*line++);
		} else {
			line++;
			loadEmbedAtlas();
		}
		values.clear();

		//get chars count
		parseLine(*line++);
		charsCount = get("count");
		values.clear();

		//get chars
		for (uint i = 0; i < charsCount; ++i) {
			parseLine(*line++);

			Glyph g = parseGlyph();
			font->glyphs.push_back(g);

			values.clear();
		}

		//get kernings
		parseLine(*line++);
		uint kernings = (uint) get("count");
		for (uint i = 0; i < kernings; ++i) {
			parseLine(*line++);

			const uint first = (uint) get("first");
			const uint second = (uint) get("second");
			const float amount = (float) get("amount");

			for (auto &&g : font->glyphs) {
				if (g.id == second) {
					g.kernings.emplace_back((float) first, amount);
					break;
				}
			}

			values.clear();
		}

		return true;
	}

	Glyph FontLoader::parseGlyph() {
		const float pad = padding[0];

		const uint id = (uint) get("id");
		const float u = (get("x") + padding[PAD_LEFT] - pad) / atlasSize;
		const float v = (get("y") + padding[PAD_TOP] - pad) / atlasSize;
		const float w = get("width") - (paddingWidth - (2.0f * pad));
		const float h = get("height") - (paddingHeight - (2.0f * pad));
		const float xo = get("xoffset") + padding[PAD_LEFT];
		const float yo = get("yoffset") + padding[PAD_TOP];
		const float xa = get("xadvance") - paddingWidth;

		return {id, {u, v}, {w / atlasSize, h / atlasSize}, {xo, yo}, {w, h}, xa};
	}

	void FontLoader::parseLine(const string &line) {
		const std::vector<string> parts = utils::splitString(line, SPLITTER);
		for (const auto &part : parts) {
			const std::vector<string> pair = utils::splitString(part, EQUAL_SPLITTER);
			if (pair.size() == 2) {
				values.emplace(pair[0], pair[1]);
			}
		}
	}

	void FontLoader::parsePadding(const string &line) {
		parseLine(line);

		const std::vector<string> v = utils::splitString(values["padding"], NUMBER_SEPARATOR);
		for (uint i = 0; i < 4; ++i) {
			padding[i] = atoi(v[i].c_str());
		}

		values.clear();

		paddingWidth = padding[PAD_LEFT] + padding[PAD_RIGHT];
		paddingHeight = padding[PAD_TOP] + padding[PAD_BOTTOM];
	}

	bool FontLoader::loadAtlas(const string &line) {
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		static TextureParameters params(TextureTarget::Tex2D,
		                                PixelInternalFormat::Rgba,
		                                PixelFormat::Rgba,
		                                PixelType::UnsignedByte);

		const wstring wide = converter.from_bytes(line);

		const size_t begin = wide.find(L"file=\"") + 6;
		const size_t end = wide.find(L'\"', begin);
		const wstring file = wide.substr(begin, end - begin);

		const size_t slash = font->path.find_last_of(L"/\\") + 1;
		const wstring path = font->path.substr(0, slash) + file;

		font->atlas = new Texture(font->name + "_atlas", path, params);

		return true;
	}

	void FontLoader::loadEmbedAtlas() {
		static TextureParameters params(TextureTarget::Tex2D,
		                                PixelInternalFormat::Rgba,
		                                PixelFormat::Rgba,
		                                PixelType::UnsignedByte);

		const uint size = internal::DEFAULT_FONT_TEXTURE_W;
		font->atlas = new Texture(font->name + "_atlas", size, size, 0, params);
		font->atlas->setData2D(internal::DEFAULT_FONT_TEXTURE);
	}

	bool FontLoader::readFile() {
		std::ifstream file(font->path.c_str());
		if (!file.is_open()) {
			XE_ERROR("[FontLoader]: couldn't open file '", font->path, "'");
			return false;
		}

		string l;
		while (std::getline(file, l)) {
			lines.push_back(l);
		}
		file.close();

		return true;
	}

	void FontLoader::loadEmbed() {
		const uint size = internal::DEFAULT_FONT_SIZE;
		const char **file = internal::DEFAULT_FONT;

		lines.reserve(size);

		for (uint i = 0; i < size; ++i) {
			lines.emplace_back(file[i]);
		}
	}

}
