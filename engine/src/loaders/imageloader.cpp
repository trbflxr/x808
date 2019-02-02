//
// Created by FLXR on 8/16/2018.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <xe/utils/log.hpp>
#include <xe/core/vfs.hpp>
#include <xe/loaders/imageloader.hpp>

namespace xe {

	byte *ImageLoader::load(const char *file, uint *width, uint *height, uint *bits) {
		string path(basePath);
		path += file;

		int64 memorySize;
		byte *memory = VFS::readFile(path, &memorySize);

		if (!memory) {
			XE_CORE_ERROR("[ImageLoader]: unable to load image: '{0}'", path);
			return nullptr;
		}

		int32 w;
		int32 h;
		int32 bpp;

		byte *data = stbi_load_from_memory(memory, memorySize, &w, &h, &bpp, 0);

		*width = (uint) w;
		*height = (uint) h;
		*bits = (uint) bpp * 8;

		return data;
	}

	byte *ImageLoader::load(const string &file, uint *width, uint *height, uint *bits) {
		return load(file.c_str(), width, height, bits);
	}

}