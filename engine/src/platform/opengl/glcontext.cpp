//
// Created by FLXR on 7/6/2018.
//

#undef NOGDI
#include <windows.h>
#define NOGDI

#include <GL/glew.h>
#include <GL/wglew.h>

#include "glcontext.hpp"
#include "utils/log.hpp"

namespace xe { namespace api {

	static HDC hDc;

	GLContext::GLContext(void *deviceContext) {
		hDc = GetDC(static_cast<HWND>(deviceContext));
		HGLRC hrc = wglCreateContext(hDc);

		if (hrc) {
			if (!wglMakeCurrent(hDc, hrc)) {
				XE_FATAL("Failed setting OpenGL context!");
			}
		} else {
			XE_FATAL("Failed creating OpenGL context!");
		}

		if (glewInit() != GLEW_OK) {
			XE_FATAL("Could not initialize GLEW!");
		}
	}

	void GLContext::swapBuffers() {
		SwapBuffers(hDc);
	}

	void GLContext::enableVsync(bool enabled) {
		wglSwapIntervalEXT(enabled);
	}

}}
