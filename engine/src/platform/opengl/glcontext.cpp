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

static HDC hDc;

xe::gfx::api::GLContext::GLContext(const xe::WindowProperties &props, void *deviceContext) {
	hDc = GetDC((HWND) deviceContext);
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

	//setting up vsync
	wglSwapIntervalEXT(props.vSync);
}

void xe::gfx::api::GLContext::swapBuffers() {
	SwapBuffers(hDc);
}
