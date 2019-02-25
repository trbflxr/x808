//
// Created by FLXR on 2/25/2019.
//

#include <xetools/spak.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace xe {

	void spak::packAtlas(const std::string &outPath, int32 width, int32 height, byte *data, bool flip) {
		stbi_flip_vertically_on_write(flip);
		stbi_write_png(outPath.c_str(), width, height, 4, data, width * 4);
	}

}
