//
// Created by FLXR on 7/6/2018.
//

#undef NOGDI

#include <windows.h>

#define NOGDI

#include <GL/glew.h>
#include <GL/wglew.h>

#include <xe/config.hpp>
#include <xe/utils/log.hpp>

#include "glcommon.hpp"
#include "glcontext.hpp"

namespace xe { namespace internal {

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

		glCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

		glCall(glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS));
	}

	void GLContext::swapBuffers() {
		SwapBuffers(hDc);
	}

	void GLContext::enableVsync(bool enabled) {
		glCall(wglSwapIntervalEXT(enabled));
	}

}}
