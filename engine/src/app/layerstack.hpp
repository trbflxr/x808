//
// Created by FLXR on 2/8/2019.
//

#ifndef X808_LAYERSTACK_HPP
#define X808_LAYERSTACK_HPP


#include <vector>
#include <xe/gfx/layer.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	namespace fx {
		class Quad;
	}

	class Application;

	class LayerStack : NonCopyable {
	public:
		explicit LayerStack(Application *app);
		~LayerStack() override;

		void render(bool renderImGui);
		void tick();

		void update(float delta);
		void lateUpdate(float delta);
		void fixedUpdate(float delta);

		void input(Event &event);

		void resize(int32 width, int32 height);

		void pushLayer(Layer *layer);
		Layer *popLayer();
		void pushOverlay(Layer *overlay);
		Layer *popOverlay();

		inline std::vector<Layer *>::iterator begin() { return layers.begin(); }
		inline std::vector<Layer *>::iterator end() { return layers.end(); }

	private:
		Application &app;

		fx::Quad *quad;

		std::vector<Layer *> layers;
		std::vector<Layer *>::iterator layerInsert;
	};

}


#endif //X808_LAYERSTACK_HPP
