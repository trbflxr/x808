//
// Created by FLXR on 7/6/2018.
//

#undef NOGDI

#include <windows.h>

#define NOGDI

#include <GL/glew.h>
#include <GL/wglew.h>

#include "glcommon.hpp"
#include "glcontext.hpp"
#include "config.hpp"
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

		if (gConfig.useSRGB) {
			glCall(glEnable(GL_FRAMEBUFFER_SRGB));
		} else {
			glCall(glDisable(GL_FRAMEBUFFER_SRGB));
		}
	}

	void GLContext::swapBuffers() {
		SwapBuffers(hDc);
	}

	void GLContext::enableVsync(bool enabled) {
		glCall(wglSwapIntervalEXT(enabled));
	}

}}
