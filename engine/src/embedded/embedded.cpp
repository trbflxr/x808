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

	///normal
	byte DEFAULT_NORMAL_ARRAY[] = {
#include "files/defaultnormal.embed"
	};

	byte *DEFAULT_NORMAL = DEFAULT_NORMAL_ARRAY;
	uint DEFAULT_NORMAL_SIZE = sizeof(DEFAULT_NORMAL_ARRAY);
	uint DEFAULT_NORMAL_W = 16;
	uint DEFAULT_NORMAL_H = 16;

	///displacement map
	byte DEFAULT_DISP_ARRAY[] = {
#include "files/defaultdisp.embed"
	};

	byte *DEFAULT_DISP = DEFAULT_DISP_ARRAY;
	uint DEFAULT_DISP_SIZE = sizeof(DEFAULT_DISP_ARRAY);
	uint DEFAULT_DISP_W = 16;
	uint DEFAULT_DISP_H = 16;

}}