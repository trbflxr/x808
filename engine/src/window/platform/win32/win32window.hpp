//
// Created by FLXR on 7/15/2018.
//

#ifndef X808_WIN32WINDOW_HPP
#define X808_WIN32WINDOW_HPP

#include <windows.h>
#include <window/platformwindow.hpp>

namespace xe { namespace internal {

	class PlatformWindowWin32 : public PlatformWindow {
	public:
		explicit PlatformWindowWin32(VideoMode mode, const wstring &title, uint style);
		~PlatformWindowWin32() override;

		void *getHandle() const override;

		vec2i getPosition() const override;
		void setPosition(const vec2i &position) const override;

		vec2i getSize() const override;
		void setSize(const vec2i &size) const override;

		void setTitle(const wstring &title) const override;
		wstring getTitle() const override;

		void setIcon(uint width, uint height, const byte *pixels) override;

		void setVisible(bool visible) const override;

		void setMouseCursorVisible(bool visible) override;
		void setMouseCursorGrabbed(bool grabbed) override;
		bool isMouseCursorGrabbed() const override;
		void setMouseCursor(const Cursor &cursor) override;

		void setKeyRepeatEnabled(bool enabled) override;

		void requestFocus() const override;
		bool hasFocus() const override;

	protected:
		void processEvents() override;

	private:
		void registerWindowClass();

		void switchToFullscreen(const VideoMode &mode);

		void cleanup();

		void processEvent(UINT message, WPARAM wParam, LPARAM lParam);

		void setTracking(bool track);

		void grabCursor(bool grabbed) const;

		static Keyboard::Key virtualKeyCodeToXE(WPARAM key, LPARAM flags);

		static LRESULT CALLBACK globalOnEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		mutable RECT rect;
		HWND handle;
		LONG_PTR callback;
		bool cursorVisible;
		HCURSOR lastCursor;
		HICON icon;
		bool keyRepeatEnabled;
		vec2i lastSize;
		bool resizing;
		uint16 surrogate;
		bool mouseInside;
		bool fullscreen;
		bool cursorGrabbed;
	};

}}


#endif //X808_WIN32WINDOW_HPP
