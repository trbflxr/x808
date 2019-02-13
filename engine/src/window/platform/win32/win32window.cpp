//
// Created by FLXR on 7/15/2018.
//

#undef NOGDI
#include <windows.h>
#define NOGDI

#include <dbt.h>
#include <xe/window/window.hpp>
#include <xe/utils/logger.hpp>
#include <xe/audio/audiomaster.hpp>
#include "win32window.hpp"

namespace {
	uint windowCount = 0;
	uint handleCount = 0;
	const wchar_t *className = L"x808_win32_window";
	xe::internal::PlatformWindowWin32 *fullscreenWindow = nullptr;
}

namespace xe { namespace internal {

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

	PlatformWindowWin32::PlatformWindowWin32(VideoMode mode, const string &title, uint style) :
			handle(nullptr),
			callback(0),
			cursorVisible(true),
			lastCursor(LoadCursor(nullptr, IDC_ARROW)),
			icon(nullptr),
			keyRepeatEnabled(true),
			lastSize(mode.width, mode.height),
			resizing(false),
			mouseInside(false),
			fullscreen((style & WindowStyle::Fullscreen) != 0),
			cursorGrabbed(fullscreen) {

		//register
		if (windowCount == 0) {
			registerWindowClass();
		}

		HDC screenDC = GetDC(nullptr);
		int32 left = (GetDeviceCaps(screenDC, HORZRES) - mode.width) / 2;
		int32 top = (GetDeviceCaps(screenDC, VERTRES) - mode.height) / 2;
		int32 width = mode.width;
		int32 height = mode.height;
		ReleaseDC(nullptr, screenDC);

		DWORD win32Style = WS_VISIBLE;
		if (style == WindowStyle::None) {
			win32Style |= WS_POPUP;
		} else {
			win32Style |= WS_POPUP;
			if (style & WindowStyle::Titlebar) win32Style |= WS_CAPTION | WS_MINIMIZEBOX;
			if (style & WindowStyle::Resize) win32Style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
			if (style & WindowStyle::Close) win32Style |= WS_SYSMENU;
		}

		if (!fullscreen) {
			RECT rectangle = {0, 0, width, height};
			AdjustWindowRect(&rectangle, win32Style, false);
			width = rectangle.right - rectangle.left;
			height = rectangle.bottom - rectangle.top;
		}

		handle = CreateWindow(className, toWstring(title).c_str(), win32Style, left, top, width, height,
		                      nullptr, nullptr, GetModuleHandle(nullptr), this);

		DEV_BROADCAST_HDR deviceBroadcastHeader = {sizeof(DEV_BROADCAST_HDR), DBT_DEVTYP_DEVICEINTERFACE, 0};
		RegisterDeviceNotification(handle, &deviceBroadcastHeader,
		                           DEVICE_NOTIFY_WINDOW_HANDLE | DEVICE_NOTIFY_ALL_INTERFACE_CLASSES);

		screenDC = GetDC(handle);
		PIXELFORMATDESCRIPTOR pfd = getPixelFormat();
		int32 pixelFormat = ChoosePixelFormat(screenDC, &pfd);

		if (pixelFormat) {
			if (!SetPixelFormat(screenDC, pixelFormat, &pfd)) {
				XE_CORE_FATAL("[PlatformWindowWin32]: Failed setting pixel format!");
			}
		} else {
			XE_CORE_FATAL("[PlatformWindowWin32]: Failed choosing pixel format!");
		}
		ReleaseDC(handle, screenDC);

		setSize(vec2(mode.width, mode.height));

		if (fullscreen) {
			switchToFullscreen(mode);
		}

		windowCount++;
	}

	PlatformWindowWin32::~PlatformWindowWin32() {
		ShowCursor(true);
		SetCursor(LoadCursor(nullptr, IDC_ARROW));

		if (icon) {
			DestroyIcon(icon);
		}

		if (handle) {
			--handleCount;
		}

		if (!callback) {
			if (handle) {
				DestroyWindow(handle);
			}

			windowCount--;

			if (windowCount == 0) {
				UnregisterClass(className, GetModuleHandle(nullptr));
			}
		} else {
			SetWindowLongPtr(handle, GWLP_WNDPROC, callback);
		}

		if (this == fullscreenWindow) {
			fullscreenWindow = nullptr;
		}
	}

	void *PlatformWindowWin32::getHandle() const {
		return handle;
	}

	vec2 PlatformWindowWin32::getPosition() const {
		RECT rect;
		GetWindowRect(handle, &rect);

		return vec2(rect.left, rect.top);
	}

	void PlatformWindowWin32::setPosition(const vec2 &position) const {
		SetWindowPos(handle, nullptr,
		             static_cast<int32>(position.x),
		             static_cast<int32>(position.y),
		             0, 0, SWP_NOSIZE | SWP_NOZORDER);

		if (cursorGrabbed) {
			grabCursor(true);
		}
	}

	vec2 PlatformWindowWin32::getSize() const {
		GetClientRect(handle, &rect);

		return vec2(rect.right - rect.left, rect.bottom - rect.top);
	}

	void PlatformWindowWin32::setSize(const vec2 &size) const {
		RECT rectangle = {0, 0, static_cast<LONG>(size.x), static_cast<LONG>(size.y)};
		AdjustWindowRect(&rectangle, static_cast<DWORD>(GetWindowLong(handle, GWL_STYLE)), false);

		const int32 width = rectangle.right - rectangle.left;
		const int32 height = rectangle.bottom - rectangle.top;

		SetWindowPos(handle, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
	}

	void PlatformWindowWin32::setTitle(const string &title) const {
		SetWindowText(handle, toWstring(title).c_str());
	}

	string PlatformWindowWin32::getTitle() const {
		std::wstring title(128, '\0');
		GetWindowText(handle, &title[0], 128);

		return toString(title);
	}

	void PlatformWindowWin32::setIcon(uint width, uint height, const byte *pixels) {
		if (icon) {
			DestroyIcon(icon);
		}

		std::vector<byte> iconPixels(width * height * 4);
		for (std::size_t i = 0; i < iconPixels.size() / 4; ++i) {
			iconPixels[i * 4 + 0] = pixels[i * 4 + 2];
			iconPixels[i * 4 + 1] = pixels[i * 4 + 1];
			iconPixels[i * 4 + 2] = pixels[i * 4 + 0];
			iconPixels[i * 4 + 3] = pixels[i * 4 + 3];
		}

		icon = CreateIcon(GetModuleHandleW(nullptr), width, height, 1, 32, nullptr, &iconPixels[0]);

		if (icon) {
			SendMessage(handle, WM_SETICON, ICON_BIG, (LPARAM) icon);
			SendMessage(handle, WM_SETICON, ICON_SMALL, (LPARAM) icon);
		} else {
			XE_CORE_ERROR("[PlatformWindowWin32]: Failed to set the window's icon");
		}
	}

	void PlatformWindowWin32::setVisible(bool visible) const {
		ShowWindow(handle, visible ? SW_SHOW : SW_HIDE);
	}

	void PlatformWindowWin32::setMouseCursorVisible(bool visible) {
		if (visible != cursorVisible) {
			cursorVisible = visible;
			ShowCursor(visible);
		}
	}

	void PlatformWindowWin32::setMouseCursorGrabbed(bool grabbed) {
		cursorGrabbed = grabbed;
		grabCursor(cursorGrabbed);
	}

	bool PlatformWindowWin32::isMouseCursorGrabbed() const {
		return cursorGrabbed;
	}

	void PlatformWindowWin32::setMouseCursor(const Cursor &cursor) {
		lastCursor = static_cast<HCURSOR>(cursor.raw());
		SetCursor(lastCursor);
	}

	void PlatformWindowWin32::setKeyRepeatEnabled(bool enabled) {
		keyRepeatEnabled = enabled;
	}

	void PlatformWindowWin32::requestFocus() const {
		DWORD thisPid = GetWindowThreadProcessId(handle, nullptr);
		DWORD foregroundPid = GetWindowThreadProcessId(GetForegroundWindow(), nullptr);

		if (thisPid == foregroundPid) {
			SetForegroundWindow(handle);
		} else {
			FLASHWINFO info;
			info.cbSize = sizeof(info);
			info.hwnd = handle;
			info.dwFlags = FLASHW_TRAY;
			info.dwTimeout = 0;
			info.uCount = 3;

			FlashWindowEx(&info);
		}
	}

	bool PlatformWindowWin32::hasFocus() const {
		return handle == GetForegroundWindow();
	}

	void PlatformWindowWin32::processEvents() {
		if (!callback) {
			MSG message;
			while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
				TranslateMessage(&message);
				DispatchMessageW(&message);
			}
		}
	}

	void PlatformWindowWin32::registerWindowClass() {
		WNDCLASSW windowClass;
		windowClass.style = 0;
		windowClass.lpfnWndProc = &PlatformWindowWin32::globalOnEvent;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = GetModuleHandleW(nullptr);
		windowClass.hIcon = nullptr;
		windowClass.hCursor = nullptr;
		windowClass.hbrBackground = nullptr;
		windowClass.lpszMenuName = nullptr;
		windowClass.lpszClassName = className;
		RegisterClass(&windowClass);
	}

	void PlatformWindowWin32::switchToFullscreen(const VideoMode &mode) {
		DEVMODE devMode;
		devMode.dmSize = sizeof(DEVMODE);
		devMode.dmPelsWidth = mode.width;
		devMode.dmPelsHeight = mode.height;
		devMode.dmBitsPerPel = mode.bitsPerPixel;
		devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

		if (ChangeDisplaySettingsW(&devMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
			XE_CORE_ERROR("[PlatformWindowWin32]: Failed to change display mode for fullscreen");
			return;
		}

		SetWindowLong(handle, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
		SetWindowLong(handle, GWL_EXSTYLE, WS_EX_APPWINDOW);

		SetWindowPos(handle, HWND_TOP, 0, 0, mode.width, mode.height, SWP_FRAMECHANGED);
		ShowWindow(handle, SW_SHOW);

		fullscreenWindow = this;
	}

	void PlatformWindowWin32::cleanup() {
		if (fullscreenWindow == this) {
			ChangeDisplaySettings(nullptr, 0);
			fullscreenWindow = nullptr;
		}

		setMouseCursorVisible(true);
		setTracking(false);

		ReleaseCapture();
	}

	void PlatformWindowWin32::setTracking(bool track) {
		TRACKMOUSEEVENT mouseEvent;
		mouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
		mouseEvent.dwFlags = track ? TME_LEAVE : TME_CANCEL;
		mouseEvent.hwndTrack = handle;
		mouseEvent.dwHoverTime = HOVER_DEFAULT;
		TrackMouseEvent(&mouseEvent);
	}

	void PlatformWindowWin32::grabCursor(bool grabbed) const {
		if (grabbed) {
			RECT rect;
			GetClientRect(handle, &rect);
			MapWindowPoints(handle, nullptr, reinterpret_cast<LPPOINT>(&rect), 2);
			ClipCursor(&rect);
		} else {
			ClipCursor(nullptr);
		}
	}


	void PlatformWindowWin32::processEvent(UINT message, WPARAM wParam, LPARAM lParam) {
		if (!handle) return;

		switch (message) {
			case WM_DESTROY: {
				cleanup();
				break;
			}

			case WM_SETCURSOR: {
				if (LOWORD(lParam) == HTCLIENT) {
					SetCursor(lastCursor);
				}
				break;
			}

			case WM_CLOSE: {
				Event event{ };
				event.type = Event::Closed;
				pushEvent(event);
				break;
			}

			case WM_SIZE: {
				if (wParam != SIZE_MINIMIZED && !resizing && lastSize != getSize()) {
					lastSize = getSize();

					Event event{ };
					event.type = Event::Resized;
					event.size.width = lastSize.x;
					event.size.height = lastSize.y;
					pushEvent(event);

					grabCursor(cursorGrabbed);
				}
				break;
			}

			case WM_ENTERSIZEMOVE: {
				resizing = true;
				grabCursor(false);
				break;
			}

			case WM_EXITSIZEMOVE: {
				resizing = false;

				if (lastSize != getSize()) {
					lastSize = getSize();

					Event event{ };
					event.type = Event::Resized;
					event.size.width = lastSize.x;
					event.size.height = lastSize.y;
					pushEvent(event);
				}

				grabCursor(cursorGrabbed);
				break;
			}

			case WM_GETMINMAXINFO: {
				MINMAXINFO *info = reinterpret_cast<MINMAXINFO *>(lParam);
				info->ptMaxTrackSize.x = 50000;
				info->ptMaxTrackSize.y = 50000;
				break;
			}

			case WM_SETFOCUS: {
				grabCursor(cursorGrabbed);

				Event event{ };
				event.type = Event::GainedFocus;
				pushEvent(event);
				break;
			}

			case WM_KILLFOCUS: {
				grabCursor(false);

				Event event{ };
				event.type = Event::LostFocus;
				pushEvent(event);
				break;
			}

			case WM_CHAR: {
				if (keyRepeatEnabled || ((lParam & (1 << 30)) == 0)) {
					uint ch = static_cast<uint>(wParam);

					Event event{ };
					event.type = Event::TextEntered;

					wcharToUTF8(ch, event.text.unicode);

					pushEvent(event);

				}
				break;
			}

			case WM_KEYDOWN:
			case WM_SYSKEYDOWN: {
				if (keyRepeatEnabled || ((HIWORD(lParam) & KF_REPEAT) == 0)) {
					Event event{ };
					event.type = Event::KeyPressed;
					event.key.alt = HIWORD(GetKeyState(VK_MENU)) != 0;
					event.key.control = HIWORD(GetKeyState(VK_CONTROL)) != 0;
					event.key.shift = HIWORD(GetKeyState(VK_SHIFT)) != 0;
					event.key.system = HIWORD(GetKeyState(VK_LWIN)) || HIWORD(GetKeyState(VK_RWIN));
					event.key.code = virtualKeyCodeToXE(wParam, lParam);
					pushEvent(event);
				}
				break;
			}

			case WM_KEYUP:
			case WM_SYSKEYUP: {
				Event event{ };
				event.type = Event::KeyReleased;
				event.key.alt = HIWORD(GetKeyState(VK_MENU)) != 0;
				event.key.control = HIWORD(GetKeyState(VK_CONTROL)) != 0;
				event.key.shift = HIWORD(GetKeyState(VK_SHIFT)) != 0;
				event.key.system = HIWORD(GetKeyState(VK_LWIN)) || HIWORD(GetKeyState(VK_RWIN));
				event.key.code = virtualKeyCodeToXE(wParam, lParam);
				pushEvent(event);
				break;
			}

			case WM_MOUSEWHEEL: {
				POINT position;
				position.x = static_cast<int16>(LOWORD(lParam));
				position.y = static_cast<int16>(HIWORD(lParam));
				ScreenToClient(handle, &position);

				int16 delta = static_cast<int16>(HIWORD(wParam));

				Event event{ };
				event.type = Event::MouseWheelMoved;
				event.mouseWheel.delta = delta / 120;
				event.mouseWheel.x = position.x;
				event.mouseWheel.y = (rect.bottom - rect.top) - position.y;
				pushEvent(event);
				break;
			}

			case WM_LBUTTONDOWN: {
				Event event{ };
				event.type = Event::MouseButtonPressed;
				event.mouseButton.button = Mouse::Left;
				event.mouseButton.x = static_cast<float>(LOWORD(lParam));
				event.mouseButton.y = (rect.bottom - rect.top) - static_cast<float>(HIWORD(lParam));
				pushEvent(event);
				break;
			}

			case WM_LBUTTONUP: {
				Event event{ };
				event.type = Event::MouseButtonReleased;
				event.mouseButton.button = Mouse::Left;
				event.mouseButton.x = static_cast<float>(LOWORD(lParam));
				event.mouseButton.y = (rect.bottom - rect.top) - static_cast<float>(HIWORD(lParam));
				pushEvent(event);
				break;
			}

			case WM_RBUTTONDOWN: {
				Event event{ };
				event.type = Event::MouseButtonPressed;
				event.mouseButton.button = Mouse::Right;
				event.mouseButton.x = static_cast<float>(LOWORD(lParam));
				event.mouseButton.y = (rect.bottom - rect.top) - static_cast<float>(HIWORD(lParam));
				pushEvent(event);
				break;
			}

			case WM_RBUTTONUP: {
				Event event{ };
				event.type = Event::MouseButtonReleased;
				event.mouseButton.button = Mouse::Right;
				event.mouseButton.x = static_cast<float>(LOWORD(lParam));
				event.mouseButton.y = (rect.bottom - rect.top) - static_cast<float>(HIWORD(lParam));
				pushEvent(event);
				break;
			}

			case WM_MBUTTONDOWN: {
				Event event{ };
				event.type = Event::MouseButtonPressed;
				event.mouseButton.button = Mouse::Middle;
				event.mouseButton.x = static_cast<float>(LOWORD(lParam));
				event.mouseButton.y = (rect.bottom - rect.top) - static_cast<float>(HIWORD(lParam));
				pushEvent(event);
				break;
			}

			case WM_MBUTTONUP: {
				Event event{ };
				event.type = Event::MouseButtonReleased;
				event.mouseButton.button = Mouse::Middle;
				event.mouseButton.x = static_cast<int16>(LOWORD(lParam));
				event.mouseButton.y = (rect.bottom - rect.top) - static_cast<int16>(HIWORD(lParam));
				pushEvent(event);
				break;
			}

			case WM_XBUTTONDOWN: {
				Event event{ };
				event.type = Event::MouseButtonPressed;
				event.mouseButton.button = HIWORD(wParam) == XBUTTON1 ? Mouse::XButton1 : Mouse::XButton2;
				event.mouseButton.x = static_cast<float>(LOWORD(lParam));
				event.mouseButton.y = (rect.bottom - rect.top) - static_cast<float>(HIWORD(lParam));
				pushEvent(event);
				break;
			}

			case WM_XBUTTONUP: {
				Event event{ };
				event.type = Event::MouseButtonReleased;
				event.mouseButton.button = HIWORD(wParam) == XBUTTON1 ? Mouse::XButton1 : Mouse::XButton2;
				event.mouseButton.x = static_cast<float>(LOWORD(lParam));
				event.mouseButton.y = (rect.bottom - rect.top) - static_cast<float>(HIWORD(lParam));
				pushEvent(event);
				break;
			}

			case WM_MOUSELEAVE: {
				if (mouseInside) {
					mouseInside = false;

					Event event{ };
					event.type = Event::MouseLeft;
					pushEvent(event);
				}
				break;
			}

			case WM_MOUSEMOVE: {
				float x = static_cast<float>(LOWORD(lParam));
				float y = static_cast<float>(HIWORD(lParam));

				RECT area;
				GetClientRect(handle, &area);

				if ((wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2)) == 0) {
					if (GetCapture() == handle) {
						ReleaseCapture();
					}
				} else if (GetCapture() != handle) {
					SetCapture(handle);
				}

				if ((x < area.left) || (x > area.right) || (y < area.top) || (y > area.bottom)) {
					if (mouseInside) {
						mouseInside = false;
						setTracking(false);

						Event event{ };
						event.type = Event::MouseLeft;
						pushEvent(event);
					}
				} else {
					if (!mouseInside) {
						mouseInside = true;
						setTracking(true);

						Event event{ };
						event.type = Event::MouseEntered;
						pushEvent(event);
					}
				}

				Event event{ };
				event.type = Event::MouseMoved;
				event.mouseMove.x = x;
				event.mouseMove.y = (rect.bottom - rect.top) - y;
				pushEvent(event);
				break;
			}

			case WM_DEVICECHANGE : {
				if (wParam == DBT_DEVICEARRIVAL) {
					auto pDev = reinterpret_cast<PDEV_BROADCAST_HDR>(lParam);
					if (pDev) {
						if (pDev->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE) {
							auto pInter = reinterpret_cast<const PDEV_BROADCAST_DEVICEINTERFACE>(pDev);
							static const GUID audioGUID = {1771351300, 37871, 4560,
							                               {163, 204, 0, 160, 201, 34, 49, 150}};
							if (pInter->dbcc_classguid == audioGUID) { }
						}
					}
				}
				break;
			}

			default: break;
		}
	}

	Keyboard::Key PlatformWindowWin32::virtualKeyCodeToXE(WPARAM key, LPARAM flags) {
		switch (key) {
			case VK_SHIFT: {
				static UINT lShift = MapVirtualKeyW(VK_LSHIFT, MAPVK_VK_TO_VSC);
				UINT scancode = static_cast<UINT>((flags & (0xFF << 16)) >> 16);
				return scancode == lShift ? Keyboard::LShift : Keyboard::RShift;
			}

			case VK_MENU : return (HIWORD(flags) & KF_EXTENDED) ? Keyboard::RAlt : Keyboard::LAlt;
			case VK_CONTROL : return (HIWORD(flags) & KF_EXTENDED) ? Keyboard::RControl : Keyboard::LControl;

			case VK_LWIN: return Keyboard::LSystem;
			case VK_RWIN: return Keyboard::RSystem;
			case VK_APPS: return Keyboard::Menu;
			case VK_OEM_1: return Keyboard::SemiColon;
			case VK_OEM_2: return Keyboard::Slash;
			case VK_OEM_PLUS: return Keyboard::Equal;
			case VK_OEM_MINUS: return Keyboard::Dash;
			case VK_OEM_4: return Keyboard::LBracket;
			case VK_OEM_6: return Keyboard::RBracket;
			case VK_OEM_COMMA: return Keyboard::Comma;
			case VK_OEM_PERIOD: return Keyboard::Period;
			case VK_OEM_7: return Keyboard::Quote;
			case VK_OEM_5: return Keyboard::BackSlash;
			case VK_OEM_3: return Keyboard::Tilde;
			case VK_ESCAPE: return Keyboard::Escape;
			case VK_SPACE: return Keyboard::Space;
			case VK_RETURN: return Keyboard::Return;
			case VK_BACK: return Keyboard::BackSpace;
			case VK_TAB: return Keyboard::Tab;
			case VK_PRIOR: return Keyboard::PageUp;
			case VK_NEXT: return Keyboard::PageDown;
			case VK_END: return Keyboard::End;
			case VK_HOME: return Keyboard::Home;
			case VK_INSERT: return Keyboard::Insert;
			case VK_DELETE: return Keyboard::Delete;
			case VK_ADD: return Keyboard::Add;
			case VK_SUBTRACT: return Keyboard::Subtract;
			case VK_MULTIPLY: return Keyboard::Multiply;
			case VK_DIVIDE: return Keyboard::Divide;
			case VK_PAUSE: return Keyboard::Pause;
			case VK_F1: return Keyboard::F1;
			case VK_F2: return Keyboard::F2;
			case VK_F3: return Keyboard::F3;
			case VK_F4: return Keyboard::F4;
			case VK_F5: return Keyboard::F5;
			case VK_F6: return Keyboard::F6;
			case VK_F7: return Keyboard::F7;
			case VK_F8: return Keyboard::F8;
			case VK_F9: return Keyboard::F9;
			case VK_F10: return Keyboard::F10;
			case VK_F11: return Keyboard::F11;
			case VK_F12: return Keyboard::F12;
			case VK_F13: return Keyboard::F13;
			case VK_F14: return Keyboard::F14;
			case VK_F15: return Keyboard::F15;
			case VK_LEFT: return Keyboard::Left;
			case VK_RIGHT: return Keyboard::Right;
			case VK_UP: return Keyboard::Up;
			case VK_DOWN: return Keyboard::Down;
			case VK_NUMPAD0: return Keyboard::Numpad0;
			case VK_NUMPAD1: return Keyboard::Numpad1;
			case VK_NUMPAD2: return Keyboard::Numpad2;
			case VK_NUMPAD3: return Keyboard::Numpad3;
			case VK_NUMPAD4: return Keyboard::Numpad4;
			case VK_NUMPAD5: return Keyboard::Numpad5;
			case VK_NUMPAD6: return Keyboard::Numpad6;
			case VK_NUMPAD7: return Keyboard::Numpad7;
			case VK_NUMPAD8: return Keyboard::Numpad8;
			case VK_NUMPAD9: return Keyboard::Numpad9;
			case 'A': return Keyboard::A;
			case 'Z': return Keyboard::Z;
			case 'E': return Keyboard::E;
			case 'R': return Keyboard::R;
			case 'T': return Keyboard::T;
			case 'Y': return Keyboard::Y;
			case 'U': return Keyboard::U;
			case 'I': return Keyboard::I;
			case 'O': return Keyboard::O;
			case 'P': return Keyboard::P;
			case 'Q': return Keyboard::Q;
			case 'S': return Keyboard::S;
			case 'D': return Keyboard::D;
			case 'F': return Keyboard::F;
			case 'G': return Keyboard::G;
			case 'H': return Keyboard::H;
			case 'J': return Keyboard::J;
			case 'K': return Keyboard::K;
			case 'L': return Keyboard::L;
			case 'M': return Keyboard::M;
			case 'W': return Keyboard::W;
			case 'X': return Keyboard::X;
			case 'C': return Keyboard::C;
			case 'V': return Keyboard::V;
			case 'B': return Keyboard::B;
			case 'N': return Keyboard::N;
			case '0': return Keyboard::Num0;
			case '1': return Keyboard::Num1;
			case '2': return Keyboard::Num2;
			case '3': return Keyboard::Num3;
			case '4': return Keyboard::Num4;
			case '5': return Keyboard::Num5;
			case '6': return Keyboard::Num6;
			case '7': return Keyboard::Num7;
			case '8': return Keyboard::Num8;
			case '9': return Keyboard::Num9;
			default: return Keyboard::Unknown;
		}
	}

	LRESULT PlatformWindowWin32::globalOnEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
		if (message == WM_CREATE) {
			LONG_PTR window = (LONG_PTR) reinterpret_cast<CREATESTRUCT *>(lParam)->lpCreateParams;
			SetWindowLongPtr(handle, GWLP_USERDATA, window);
		}

		auto *window = handle ? reinterpret_cast<PlatformWindowWin32 *>(GetWindowLongPtr(handle, GWLP_USERDATA))
		                      : nullptr;

		if (window) {
			window->processEvent(message, wParam, lParam);

			if (window->callback) {
				return CallWindowProc(reinterpret_cast<WNDPROC>(window->callback),
				                      handle, message, wParam, lParam);
			}
		}

		if (message == WM_CLOSE) {
			return 0;
		}

		if ((message == WM_SYSCOMMAND) && (wParam == SC_KEYMENU)) {
			return 0;
		}

		return DefWindowProcW(handle, message, wParam, lParam);
	}

}}