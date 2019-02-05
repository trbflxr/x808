//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_GLCOMMON_HPP
#define X808_GLCOMMON_HPP


#include <xe/xeint.hpp>

namespace xe { namespace internal {

	uint glCheckError();

	bool glLogCall(const char *function, const char *file, uint line);

}}

#ifdef XE_DEBUG
#define glCall(x) ::xe::internal::glCheckError();\
        x; \
        if (!::xe::internal::glLogCall(#x, __FILE__, __LINE__)) __debugbreak();
#else
#define glCall(x) x
#endif //XE_DEBUG


#endif //X808_GLCOMMON_HPP
