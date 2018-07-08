//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_LAYER_HPP
#define X808_LAYER_HPP


#include "events/events.hpp"
#include "application/application.hpp"
#include "utils/timestep.hpp"

namespace xe { namespace gfx {

	class Layer : public IEventListener {
	public:
		virtual ~Layer() = default;

		inline bool isVisible() const { return visible; }
		inline void setVisible(bool visible) { Layer::visible = visible; }

		virtual void init() { }

		virtual void render() { }

		virtual void tick() { }

		virtual void update(const TimeStep &ts) { }

		void onEvent(Event &event) override {
			EventDispatcher dispatcher(event);

			dispatcher.dispatch<WindowResizeEvent>(
					[this](WindowResizeEvent &e) {
						return resize(e.getWidth(), e.getHeight());
					});
		}

	protected:
		explicit Layer() :
				app(Application::getApplication()),
				window(*Window::getWindowClass(nullptr)),
				visible(true) { }

		virtual bool resize(uint width, uint height) { }

	protected:
		Application &app;
		Window &window;
		bool visible;
	};

}}


#endif //X808_LAYER_HPP
