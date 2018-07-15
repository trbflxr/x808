//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_LAYER_HPP
#define X808_LAYER_HPP


#include "window/event.hpp"
#include "application/application.hpp"

namespace xe { namespace gfx {

	class Layer {
	public:
		virtual ~Layer() = default;

		inline bool isVisible() const { return visible; }
		inline void setVisible(bool visible) { Layer::visible = visible; }

		virtual void init() { }

		virtual void render() { }

		virtual void tick() { }

		virtual void update(float delta) { }
		virtual void fixedUpdate(float delta) { }

		virtual void input(Event &event) { }

	protected:
		explicit Layer() :
				app(Application::get()),
				window(app.getWindow()),
				visible(true) { }

		virtual bool resize(uint width, uint height) { }

	protected:
		Application &app;
		Window &window;
		bool visible;
	};

}}


#endif //X808_LAYER_HPP
