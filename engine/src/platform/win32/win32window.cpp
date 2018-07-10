//
// Created by FLXR on 7/6/2018.
//

#undef NOGDI

#include <windows.h>
#include <windowsx.h>

#define NOGDI

#include "application/window.hpp"
#include "utils/log.hpp"
#include "gfx/api/context.hpp"
#include "gfx/renderer.hpp"


EXTERN_C IMAGE_DOS_HEADER __ImageBase;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

HINSTANCE hInstance;
HDC hDc;
HWND hWnd;

static PIXELFORMATDESCRIPTOR getPixelFormat() {
	PIXELFORMATDESCRIPTOR result = { };
	result.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	result.nVersion = 1;
	result.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	result.iPixelType = PFD_TYPE_RGBA;
	result.cColorBits = 32;
	result.cDepthBits = 24;
	result.cStencilBits = 8;
	result.cAuxBuffers = 0;
	result.iLayerType = PFD_MAIN_PLANE;
	return result;
}

bool xe::Window::platformInit() {
	hInstance = (HINSTANCE) &__ImageBase;

	WNDCLASS winClass = { };
	winClass.hInstance = hInstance;
	winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winClass.lpfnWndProc = (WNDPROC) WndProc;
	winClass.lpszClassName = "x808_win32_window";
	winClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	winClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);

	if (!RegisterClassA(&winClass)) {
		XE_FATAL("Could not register Win32 class!");
		return false;
	}

	RECT size = {0, 0, (LONG) props.width, (LONG) props.height};
	AdjustWindowRectEx(&size, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, false,
	                   WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

	hWnd = CreateWindowExA(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
	                       winClass.lpszClassName, props.title.c_str(),
	                       WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
	                       GetSystemMetrics(SM_CXSCREEN) / 2 - props.width / 2,
	                       GetSystemMetrics(SM_CYSCREEN) / 2 - props.height / 2,
	                       size.right + (-size.left), size.bottom + (-size.top), nullptr, nullptr, hInstance,
	                       nullptr);

	if (!hWnd) {
		XE_FATAL("Could not create window!");
		return false;
	}

	registerWindowClass(hWnd, this);

	hDc = GetDC(hWnd);
	PIXELFORMATDESCRIPTOR pfd = getPixelFormat();
	int32 pixelFormat = ChoosePixelFormat(hDc, &pfd);

	if (pixelFormat) {
		if (!SetPixelFormat(hDc, pixelFormat, &pfd)) {
			XE_FATAL("Failed setting pixel format!");
			return false;
		}
	} else {
		XE_FATAL("Failed choosing pixel format!");
		return false;
	}


	gfx::api::Context::create(props, hWnd);

	ShowWindow(hWnd, SW_SHOW);
	SetFocus(hWnd);

	return true;
}


void xe::Window::platformUpdate() {
	MSG message;
	while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) > 0) {
		if (message.message == WM_QUIT) {
			closed = true;
			return;
		}
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	inputManager->platformUpdate();
	gfx::Renderer::flush();
}

void xe::Window::setTitle(const std::string_view &title) {
	props.title = title;
	SetWindowText(hWnd, title.data());
}

void xe::focusCallback(xe::Window *window, bool focused) {
	if (!focused) {
		window->inputManager->clearKeys();
		window->inputManager->clearMouseButtons();
	}
}

void xe::resizeCallback(xe::Window *window, uint width, uint height) {
	window->props.width = width;
	window->props.height = height;

	//todo: scale font

	if (window->eventCallback) {
		auto e = WindowResizeEvent(width, height);
		window->eventCallback(e);
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	LRESULT result = 0;

	xe::Window *window = xe::Window::getWindowClass(hwnd);
	if (window == nullptr) return DefWindowProc(hwnd, msg, wparam, lparam);

	xe::InputManager *inputManager = window->getInputManager();

	switch (msg) {
		case WM_ACTIVATE: {
			if (!HIWORD(wparam)) // Is minimized
			{
				// active
			} else {
				// inactive
			}

			return 0;
		}
		case WM_SYSCOMMAND: {
			switch (wparam) {
				case SC_SCREENSAVE:
				case SC_MONITORPOWER: return 0;
				default:break;
			}
			result = DefWindowProc(hwnd, msg, wparam, lparam);
		}
			break;
		case WM_SETFOCUS: xe::focusCallback(window, true);
			break;

		case WM_KILLFOCUS: xe::focusCallback(window, false);
			break;

		case WM_CLOSE:
		case WM_DESTROY: PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
			xe::keyCallback(inputManager, static_cast<int32>(lparam), static_cast<int32>(wparam), msg);
			break;

		case WM_MOUSEWHEEL:
			xe::mouseWheelCallback(inputManager, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam),
			                       GET_WHEEL_DELTA_WPARAM(wparam));
			break;

		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP: xe::mouseButtonCallback(inputManager, msg, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
			break;

		case WM_SIZE: resizeCallback(window, LOWORD(lparam), HIWORD(lparam));
			break;

		default: result = DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return result;
}