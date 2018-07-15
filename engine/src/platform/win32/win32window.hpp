//
// Created by FLXR on 7/15/2018.
//

#ifndef X808_WIN32WINDOW_HPP
#define X808_WIN32WINDOW_HPP

#include <windows.h>
#include "window/platformwindow.hpp"

namespace xe { namespace internal {

	class PlatformWindowWin32 : public PlatformWindow {
	public:
		explicit PlatformWindowWin32(VideoMode mode, const std::string_view &title, uint style);
		~PlatformWindowWin32() override;

		void *getHandle() const override;

		vec2i getPosition() const override;
		void setPosition(const vec2i &position) override;

		vec2u getSize() const override;
		void setSize(const vec2u &size) override;

		void setTitle(const std::string_view &title) override;

		void setIcon(uint width, uint height, const byte *pixels) override;

		void setVisible(bool visible) override;

		void setMouseCursorVisible(bool visible) override;
		void setMouseCursorGrabbed(bool grabbed) override;
		bool isMouseCursorGrabbed() override;
		void setMouseCursor(const Cursor &cursor) override;

		void setKeyRepeatEnabled(bool enabled) override;

		void requestFocus() override;
		bool hasFocus() const override;

	protected:
		void processEvents() override;

	private:
		void registerWindowClass();

		void switchToFullscreen(const VideoMode &mode);

		void cleanup();

		void processEvent(UINT message, WPARAM wParam, LPARAM lParam);

		void setTracking(bool track);

		void grabCursor(bool grabbed);

		static Keyboard::Key virtualKeyCodeToXE(WPARAM key, LPARAM flags);

		static LRESULT CALLBACK globalOnEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND handle;
		LONG_PTR callback;
		bool cursorVisible;
		HCURSOR lastCursor;
		HICON icon;
		bool keyRepeatEnabled;
		vec2u lastSize;
		bool resizing;
		uint16 surrogate;
		bool mouseInside;
		bool fullscreen;
		bool cursorGrabbed;
	};

}}


#endif //X808_WIN32WINDOW_HPP
