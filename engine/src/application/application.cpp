//
// Created by FLXR on 6/29/2018.
//

#include "application.hpp"
#include "gfx/layers/layer.hpp"

namespace xe {

	Application *Application::instance = nullptr;


	void Application::init() {
		platformInit();
	}

	void Application::tick() {
		for (auto &&layer : layerStack) {
			layer->tick();
		}
	}

	void Application::update(float delta) {
		for (auto &&layer : layerStack) {
			layer->update(delta);
		}
	}

	void Application::fixedUpdate(float delta) {
		for (auto &&layer : layerStack) {
			layer->fixedUpdate(delta);
		}
	}

	void Application::render() {
		for (auto &&layer : layerStack) {
			if (layer->isVisible()) {
				layer->render();
			}
		}
	}

	void Application::onEvent(Event &event) {
		for (int i = static_cast<int32>(layerStack.size() - 1); i >= 0; i--) {
			layerStack[i]->onEvent(event);
			if (event.isHandled()) return;
		}
	}

	void Application::pushLayer(gfx::Layer *layer) {
		layerStack.push_back(layer);
		layer->init();
	}

	gfx::Layer *Application::popLayer() {
		gfx::Layer *layer = layerStack.back();
		layerStack.pop_back();
		return layer;
	}

	gfx::Layer *Application::popLayer(gfx::Layer *layer) {
		for (uint i = 0; i < layerStack.size(); i++) {
			if (layerStack[i] == layer) {
				layerStack.erase(layerStack.begin() + i);
				break;
			}
		}
		return layer;
	}

}