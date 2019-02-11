//
// Created by FLXR on 8/16/2018.
//

#include <xe/utils/logger.hpp>
#include <xe/core/vfs.hpp>
#include <xe/loaders/imageloader.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace xe {

	byte *ImageLoader::load(const char *file, uint *width, uint *height, uint *bits, bool *transparency) {
		string path(basePath);
		path += file;

		int64 memorySize;
		byte *memory = VFS::readFile(path, &memorySize);

		if (!memory) {
			XE_CORE_ERROR("[ImageLoader]: unable to load image: '", path, "'");
			return nullptr;
		}

		int32 w;
		int32 h;
		int32 bpp;

		byte *data = stbi_load_from_memory(memory, memorySize, &w, &h, &bpp, STBI_rgb_alpha);

		if (width) *width = (uint) w;
		if (height) *height = (uint) h;
		if (bits) *bits = (uint) bpp * 8;
		if (transparency) *transparency = false;

		for (int32 i = 3; i < w * h; i += 4) {
			if (data[i] < 1) {
				if (transparency) *transparency = true;
				break;
			}
		}

		return data;
	}

	byte *ImageLoader::load(const string &file, uint *width, uint *height, uint *bits, bool *transparency) {
		return load(file.c_str(), width, height, bits, transparency);
	}

}