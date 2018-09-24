//
// Created by FLXR on 8/16/2018.
//

#include <stb_image.h>
#include <xe/utils/log.hpp>
#include <xe/loaders/imageloader.hpp>

namespace xe {

	byte *ImageLoader::load(const wchar_t *path, uint *width, uint *height, uint *bits) {
		int32 w;
		int32 h;
		int32 bpp;

		FILE *file = _wfopen(path, L"rb");

		byte *data = stbi_load_from_file(file, &w, &h, &bpp, 0);

		fclose(file);

		*width = (uint) w;
		*height = (uint) h;
		*bits = (uint) bpp * 8;

		return data;
	}

	byte *ImageLoader::load(const wstring &path, uint *width, uint *height, uint *bits) {
		return load(path.c_str(), width, height, bits);
	}

}