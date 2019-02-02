//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_GLCOMMON_HPP
#define X808_GLCOMMON_HPP


#include <GL/glew.h>
#include <xe/xeint.hpp>
#include <xe/utils/log.hpp>

namespace xe { namespace internal {
	static uint glCheckError() {
		return glGetError();
	}

	static bool glLogCall(const char *function, const char *file, uint line) {
		uint error = glCheckError();
		if (error != GL_NO_ERROR) {
			char buffer[1024 * 10];
			sprintf(buffer, "[OpenGL Error] (%u): %s, %s: %u", error, function, file, line);
			XE_CORE_FATAL(buffer);
			return false;
		}
		return true;
	}
}}

#ifdef XE_DEBUG
#define glCall(x) xe::internal::glCheckError();\
        x; \
        if (!xe::internal::glLogCall(#x, __FILE__, __LINE__)) __debugbreak();
#else
#define glCall(x) x
#endif //XE_DEBUG


#endif //X808_GLCOMMON_HPP
