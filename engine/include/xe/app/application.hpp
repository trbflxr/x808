//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_APPLICATION_HPP
#define X808_APPLICATION_HPP


#include <xe/common.hpp>
#include <xe/config.hpp>
#include <xe/gfx/context.hpp>
#include <xe/window/window.hpp>

namespace xe {

	class Layer;

	class XE_API Application {
	public:
		explicit Application(const Config &config, const wstring &title);
		virtual ~Application() = default;

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

		inline vec2 getWindowSize() const { return window.getSize(); }

		inline static Application &get() { return *instance; }

	private:
		void init(const wstring &title);

		void run();

		void tick();

		void update(float delta);
		void lateUpdate(float delta);
		void fixedUpdate(float delta);

		void render();

		void processEvents();

	private:
		Config config;
		Window window;

		bool running;
		bool suspend_;

		uint fps;
		uint ups;
		float frameTime;

		std::vector<Layer *> layerStack;

		static Application *instance;

	};

}


#endif //X808_APPLICATION_HPP
