//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_APPLICATION_HPP
#define X808_APPLICATION_HPP


#include "common.hpp"
#include "config.hpp"
#include "window.hpp"
#include "utils/timer.hpp"
#include "utils/timestep.hpp"

namespace xe {

	class XE_API Application {
	public:
		explicit Application(const Config& config);
		virtual ~Application();

		virtual void init();

		void start();
		void suspend();
		void resume();
		void stop();

		inline uint getFPS() const { return fps; }
		inline uint getUPS() const { return ups; }
		inline float getFrameTime() const { return frameTime; }

		inline Window &getWindow() { return *window; }
		inline const Window &getWindow() const { return *window; }

		inline uint getWindowWidth() const { return window->getWidth(); }
		inline uint getWindowHeight() const { return window->getHeight(); }

		inline static Application &getApplication() { return *instance; }

	private:
		void platformInit();
		void run();

		void tick();
		void update(const TimeStep &ts);
		void render();
		void onEvent(Event &event);

	private:
		bool running;
		bool suspend_;

		Timer *timer;

		uint fps;
		uint ups;
		float frameTime;

		Config config;

		Window *window;

		//todo: layer stack?

		static Application *instance;

	};

}


#endif //X808_APPLICATION_HPP
