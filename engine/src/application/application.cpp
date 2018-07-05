//
// Created by FLXR on 6/29/2018.
//

#include "application.hpp"
#include "gfx/renderer2d.hpp"
#include "resources/fontmanager.hpp"
#include "resources/texturemanager.hpp"

xe::Application *xe::Application::instance = nullptr;


void xe::Application::init() {
	platformInit();
}

void xe::Application::tick() {
	for (auto &&layer : layerStack) {
		layer->tick();
	}
}

void xe::Application::update(const xe::TimeStep &ts) {
	for (auto &&layer : layerStack) {
		layer->update(ts);
	}
}

void xe::Application::render() {
	for (auto &&layer : layerStack) {
		if (layer->isVisible()) {
			layer->render();
		}
	}
}

void xe::Application::onEvent(xe::Event &event) {
	for (int i = static_cast<int32>(layerStack.size() - 1); i >= 0; i--) {
		layerStack[i]->onEvent(event);
		if (event.isHandled()) return;
	}
}

void xe::Application::pushLayer(xe::gfx::Layer *layer) {
	layerStack.push_back(layer);
	layer->init();
}

xe::gfx::Layer *xe::Application::popLayer() {
	gfx::Layer *layer = layerStack.back();
	layerStack.pop_back();
	return layer;
}

xe::gfx::Layer *xe::Application::popLayer(xe::gfx::Layer *layer) {
	for (uint i = 0; i < layerStack.size(); i++) {
		if (layerStack[i] == layer) {
			layerStack.erase(layerStack.begin() + i);
			break;
		}
	}
	return layer;
}