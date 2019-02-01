//
// Created by FLXR on 8/16/2018.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <xe/utils/log.hpp>
#include <xe/loaders/imageloader.hpp>

namespace xe {

	byte *ImageLoader::load(const char *path, uint *width, uint *height, uint *bits) {
		int32 w;
		int32 h;
		int32 bpp;

		FILE *file = fopen(path, "rb");

		byte *data = stbi_load_from_file(file, &w, &h, &bpp, 0);

		fclose(file);

		*width = (uint) w;
		*height = (uint) h;
		*bits = (uint) bpp * 8;

		return data;
	}

	byte *ImageLoader::load(const string &path, uint *width, uint *height, uint *bits) {
		return load(path.c_str(), width, height, bits);
	}

}