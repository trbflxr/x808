//
// Created by FLXR on 7/3/2018.
//

#include "embedded.hpp"


namespace xe { namespace internal {

	///texture
	byte DEFAULT_TEXTURE_ARRAY[] = {
#include "files/errortexture.embed"
	};

	byte *DEFAULT_TEXTURE = DEFAULT_TEXTURE_ARRAY;
	uint DEFAULT_TEXTURE_SIZE = sizeof(DEFAULT_TEXTURE_ARRAY);
	uint DEFAULT_TEXTURE_W = 256;
	uint DEFAULT_TEXTURE_H = 256;


	///font
	byte DEFAULT_FONT_DATA_ARRAY[] = {
#include "files/consolata.embed"
	};

	byte* DEFAULT_FONT_DATA = DEFAULT_FONT_DATA_ARRAY;
	uint DEFAULT_FONT_DATA_SIZE = sizeof(DEFAULT_FONT_DATA_ARRAY);


}}