//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_APPLICATION_HPP
#define X808_APPLICATION_HPP


#include "common.hpp"
#include "config.hpp"
#include "window.hpp"
#include "utils/timer.hpp"
#include "gfx/api/context.hpp"
#include "ecs/ecs.hpp"


namespace xe { namespace gfx {
	class Layer;
}}

namespace xe {

	class XE_API Application {
	public:
		explicit Application(const Config &config, gfx::api::RenderAPI api);
		virtual ~Application();

		virtual void init();

		void pushLayer(gfx::Layer *layer);
		gfx::Layer *popLayer();
		gfx::Layer *popLayer(gfx::Layer *layer);

		void start();
		void suspend();
		void resume();
		void stop();

		inline uint getFPS() const { return fps; }
		inline uint getUPS() const { return ups; }
		inline float getFrameTime() const { return frameTime; }

		inline Window &getWindow() { return *window; }
		inline const Window &getWindow() const { return *window; }

		inline const Config &getConfig() const { return config; }

		inline uint getWindowWidth() const { return window->getWidth(); }
		inline uint getWindowHeight() const { return window->getHeight(); }

		inline ECS &getEcs() { return ecs; }

		inline static Application &get() { return *instance; }

	private:
		void platformInit();
		void run();

		void tick();
		void update(float delta);
		void fixedUpdate(float delta);
		void render();
		void onEvent(Event &event);

	private:
		bool running;
		bool suspend_;

		uint fps;
		uint ups;
		float frameTime;

		Config config;
		Window *window;

		ECS ecs;

		std::vector<gfx::Layer *> layerStack;

		static Application *instance;

	};

}


#endif //X808_APPLICATION_HPP
