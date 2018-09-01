//
// Created by FLXR on 7/3/2018.
//

#include "embedded.hpp"


namespace xe { namespace internal {

	byte DEFAULT_FONT_ARRAY[] = {
#include "files/sourcesanspro-light.embed"
	};

	byte *DEFAULT_FONT = DEFAULT_FONT_ARRAY;
	uint DEFAULT_FONT_SIZE = sizeof(DEFAULT_FONT_ARRAY);


	///texture
	byte DEFAULT_TEXTURE_ARRAY[] = {
#include "files/errortexture.embed"
	};

	byte *DEFAULT_TEXTURE = DEFAULT_TEXTURE_ARRAY;
	uint DEFAULT_TEXTURE_SIZE = sizeof(DEFAULT_TEXTURE_ARRAY);
	uint DEFAULT_TEXTURE_W = 247;
	uint DEFAULT_TEXTURE_H = 200;

}}