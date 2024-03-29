//
// Created by FLXR on 7/15/2018.
//

#ifndef X808_PLATFORMWINDOW_HPP
#define X808_PLATFORMWINDOW_HPP


#include <queue>
#include <xe/string.hpp>
#include <xe/window/videomode.hpp>
#include <xe/window/cursor.hpp>
#include <xe/window/event.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe::internal {

  class PlatformWindow : NonCopyable {
  public:
    static PlatformWindow *create(VideoMode mode, const string &title, uint style);

    bool popEvent(Event &event, bool block);

    virtual void *getHandle() const = 0;

    virtual vec2 getPosition() const = 0;
    virtual void setPosition(const vec2 &position) const = 0;

    virtual vec2 getSize() const = 0;
    virtual void setSize(const vec2 &size) const = 0;

    virtual void setTitle(const string &title) const = 0;
    virtual string getTitle() const = 0;

    virtual void setIcon(uint width, uint height, const byte *pixels) = 0;

    virtual void setVisible(bool visible) const = 0;

    virtual void setMouseCursorVisible(bool visible) = 0;
    virtual void setMouseCursorGrabbed(bool grabbed) = 0;
    virtual bool isMouseCursorGrabbed() const = 0;
    virtual void setMouseCursor(const Cursor &cursor) = 0;

    virtual void setKeyRepeatEnabled(bool enabled) = 0;

    virtual void requestFocus() const = 0;
    virtual bool hasFocus() const = 0;

  protected:
    void pushEvent(const Event &event);

    virtual void processEvents() = 0;

  private:
    std::queue<Event> events;
  };

}


#endif //X808_PLATFORMWINDOW_HPP
