//
// Created by FLXR on 2/25/2019.
//

#include <xetools/spak.hpp>
#include <xe/math/rect.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace xe {

	void spak::packAtlas(const std::string &outPath, int32 width, int32 height,
	                     const std::vector<std::pair<string, rect>> &sprites, byte *data, bool flip) {

		for (const auto &s : sprites) {
			printf("%s -> %f\n", s.first.c_str(), s.second.x);
		}


		stbi_flip_vertically_on_write(flip);
		stbi_write_png(outPath.c_str(), width, height, 4, data, width * 4);
	}

}
