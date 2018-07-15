//
// Created by FLXR on 7/14/2018.
//

#ifndef X808_WINDOW_HPP
#define X808_WINDOW_HPP


#include <string>
#include "common.hpp"
#include "event.hpp"
#include "cursor.hpp"
#include "videomode.hpp"
#include "utils/timer.hpp"

namespace xe {

	namespace internal {
		class PlatformWindow;
	}

	enum WindowStyle {
		None = 0,      // no border / title bar
		Titlebar = 1 << 0, // title bar, fixed border
		Resize = 1 << 1, // title bar, resizable border, maximize button
		Close = 1 << 2, // title bar, close button
		Fullscreen = 1 << 3, // fullscreen mode

		Default = Titlebar | Resize | Close
	};

	class XE_API Window : NonCopyable {
	public:

		Window();
		explicit Window(VideoMode mode, const std::string_view &title, uint style = WindowStyle::Default);
		~Window() override;

		void create(VideoMode mode, const std::string_view &title, uint style = WindowStyle::Default);

		void close();
		bool isOpen() const;

		bool pollEvent(Event &event);

		vec2i getPosition() const;
		void setPosition(const vec2i &position);

		inline vec2u getSize() const { return size; };
		void setSize(const vec2u &size);

		void setTitle(const std::string_view &title);

		void setIcon(uint width, uint height, const byte *pixels);

		void setVisible(bool visible);

		void setVerticalSyncEnabled(bool enabled);

		void setMouseCursorVisible(bool visible);
		void setMouseCursorGrabbed(bool grabbed);
		bool isMouseCursorGrabbed();
		void setMouseCursor(const Cursor &cursor);

		void setKeyRepeatEnabled(bool enabled);

		void setFramerateLimit(uint limit);

		void requestFocus();
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

		vec2u size;
		Timer timer;
		float frameTimeLimit;

	};

}


#endif //X808_WINDOW_HPP
