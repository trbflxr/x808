//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_APPLICATION_HPP
#define X808_APPLICATION_HPP


#include "common.hpp"
#include "config.hpp"
#include "window/window.hpp"
#include "utils/timer.hpp"
#include "gfx/api/context.hpp"
#include "ecs/ecs.hpp"

namespace xe {

	class Layer;

	class XE_API Application {
	public:
		explicit Application(const Config &config, api::RenderAPI api);
		virtual ~Application();

		void pushLayer(Layer *layer);
		Layer *popLayer();
		Layer *popLayer(Layer *layer);

		void start();
		void suspend();
		void resume();
		void stop();

		inline uint getFPS() const { return fps; }
		inline uint getUPS() const { return ups; }
		inline float getFrameTime() const { return frameTime; }

		inline Window &getWindow() { return window; }
		inline const Window &getWindow() const { return window; }

		inline const Config &getConfig() const { return config; }

		inline vec2u getWindowSize() const { return window.getSize(); }

		inline static Application &get() { return *instance; }

	private:
		void init();

		void platformInit();
		void run();

		void tick();

		void update(float delta);
		void lateUpdate(float delta);
		void fixedUpdate(float delta);

		void render();

		void processEvents();

	private:
		bool running;
		bool suspend_;

		uint fps;
		uint ups;
		float frameTime;

		Config config;
		Window window;

		std::vector<Layer *> layerStack;

		static Application *instance;

	};

}


#endif //X808_APPLICATION_HPP
