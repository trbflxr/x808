//
// Created by FLXR on 6/28/2018.
//

#undef NOGDI

#include <windows.h>

#define NOGDI

#include <GL/glew.h>
#include <GL/wglew.h>

#include "context.hpp"
#include "utils/log.hpp"

xe::gfx::api::Context *xe::gfx::api::Context::context = nullptr;

static HDC hDc;

void xe::gfx::api::Context::create(void *deviceContext, bool vSync) {
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
	wglSwapIntervalEXT(vSync);
}

void xe::gfx::api::Context::swapBuffers() {
	SwapBuffers(hDc);
}
