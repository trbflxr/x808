//
// Created by FLXR on 7/14/2018.
//

#ifndef X808_WINDOW_HPP
#define X808_WINDOW_HPP


#include <xe/common.hpp>
#include <xe/window/event.hpp>
#include <xe/window/cursor.hpp>
#include <xe/window/videomode.hpp>
#include <xe/utils/timer.hpp>
#include <xe/string.hpp>

namespace xe {

	namespace internal {
		class PlatformWindow;
	}

	enum WindowStyle {
		None = 0,            // no border / title bar
		Titlebar = BIT(0),   // title bar, fixed border
		Resize = BIT(1),     // title bar, resizable border, maximize button
		Close = BIT(2),      // title bar, close button
		Fullscreen = BIT(3), // fullscreen mode

		Default = Titlebar | Resize | Close
	};

	class XE_API Window : NonCopyable {
	public:

		Window();
		explicit Window(VideoMode mode, const string &title, uint style = WindowStyle::Default);
		~Window() override;

		void create(VideoMode mode, const string &title, uint style = WindowStyle::Default);

		void close();
		bool isOpen() const;

		bool pollEvent(Event &event);

		vec2 getPosition() const;
		void setPosition(const vec2 &position) const;

		inline vec2 getSize() const { return size; };
		void setSize(const vec2 &size);

		void setTitle(const string &title) const;
		string getTitle() const;

		void setIcon(uint width, uint height, const byte *pixels) const;

		void setVisible(bool visible) const;

		void setVerticalSyncEnabled(bool enabled) const;

		void setMouseCursorVisible(bool visible) const;
		void setMouseCursorGrabbed(bool grabbed) const;
		bool isMouseCursorGrabbed() const;
		void setMouseCursor(const Cursor &cursor) const;

		void setKeyRepeatEnabled(bool enabled) const;

		void setFramerateLimit(uint limit);

		void requestFocus() const;
		bool hasFocus() const;

		void clear() const;
		void update();

		void *getHandle() const;

	protected:
		virtual void onCreate() { };
		virtual void onResize() { };

	private:
		bool filterEvent(const Event &event);

		void init();

	private:
		internal::PlatformWindow *window;

		vec2 size;
		Timer timer;
		float frameTimeLimit;

	};

}


#endif //X808_WINDOW_HPP
