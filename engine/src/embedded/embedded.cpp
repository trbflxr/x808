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


	///font texture
	byte DEFAULT_FONT_TEXTURE_ARRAY[] = {
#include "files/consolatatex.embed"
	};

	byte *DEFAULT_FONT_TEXTURE = DEFAULT_FONT_TEXTURE_ARRAY;
	uint DEFAULT_FONT_TEXTURE_SIZE = sizeof(DEFAULT_FONT_TEXTURE_ARRAY);
	uint DEFAULT_FONT_TEXTURE_W = 1024;


	///font file
	const char *DEFAULT_FONT_ARRAY[] = {
#include "files/consolatafnt.embed"
	};

	uint DEFAULT_FONT_SIZE = 168;
	const char **DEFAULT_FONT = DEFAULT_FONT_ARRAY;

}}