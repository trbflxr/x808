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

}}