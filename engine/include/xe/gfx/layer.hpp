//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_LAYER_HPP
#define X808_LAYER_HPP


#include <xe/window/event.hpp>
#include <xe/app/application.hpp>
#include <xe/gfx/texture.hpp>

namespace xe {

	class XE_API Layer {
	public:
		virtual ~Layer() = default;

		inline bool isVisible() const { return visible; }
		inline void setVisible(bool visible) { Layer::visible = visible; }

		virtual void init() { }

		virtual void render() { }

		virtual void renderImGui() { }

		virtual void tick() { }

		virtual void update(float delta) { }
		virtual void lateUpdate(float delta) { }
		virtual void fixedUpdate(float delta) { }

		virtual void input(Event &event) { }

		virtual const Texture *getRenderTexture() const = 0;

	protected:
		explicit Layer() :
				app(Application::get()),
				window(app.getWindow()),
				visible(true) { }

		virtual void resize(int32 width, int32 height) { }

	protected:
		Application &app;
		Window &window;
		bool visible;

	private:
		friend class LayerStack;
	};

}


#endif //X808_LAYER_HPP
