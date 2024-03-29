//
// Created by FLXR on 7/15/2018.
//

#ifndef X808_WIN32WINDOW_HPP
#define X808_WIN32WINDOW_HPP

#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#ifndef WIN32_EXTRA_LEAN
  #define WIN32_EXTRA_LEAN
#endif
#include <windows.h>
#include <window/platformwindow.hpp>

namespace xe::internal {

  class PlatformWindowWin32 : public PlatformWindow {
  public:
    explicit PlatformWindowWin32(VideoMode mode, const string &title, uint style);
    ~PlatformWindowWin32() override;

    void *getHandle() const override;

    vec2 getPosition() const override;
    void setPosition(const vec2 &position) const override;

    vec2 getSize() const override;
    void setSize(const vec2 &size) const override;

    void setTitle(const string &title) const override;
    string getTitle() const override;

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
    vec2 lastSize;
    bool resizing;
    bool mouseInside;
    bool fullscreen;
    bool cursorGrabbed;
  };

}


#endif //X808_WIN32WINDOW_HPP
