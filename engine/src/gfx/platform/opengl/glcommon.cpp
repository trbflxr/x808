//
// Created by FLXR on 2/5/2019.
//

#include <cstdio>
#include <GL/glew.h>
#include <xe/utils/logger.hpp>
#include "glcommon.hpp"

namespace xe { namespace internal {

	uint glCheckError() {
		return glGetError();
	}

	bool glLogCall(const char *function, const char *file, uint line) {
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