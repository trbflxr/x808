//
// Created by FLXR on 2/8/2019.
//

#include <xe/gfx/renderer.hpp>
#include <xe/gfx/fx/quad.hpp>
#include "layerstack.hpp"

namespace xe {

	LayerStack::LayerStack(Application *app) :
			app(*app) {

		layerInsert = layers.begin();

		quad = new fx::Quad(static_cast<uint>(app->getWindowSize().x),
		                    static_cast<uint>(app->getWindowSize().y));
	}

	LayerStack::~LayerStack() {
		for (const auto &l : layers) {
			delete l;
		}

		delete quad;
	}

	void LayerStack::pushLayer(Layer *layer) {
		layerInsert = layers.emplace(layerInsert, layer);
		layer->init();
	}

	Layer *LayerStack::popLayer() {
		Layer *layer = *layerInsert;
		layers.erase(layerInsert);
		--layerInsert;
		return layer;
	}

	void LayerStack::pushOverlay(Layer *overlay) {
		layers.push_back(overlay);
	}

	Layer *LayerStack::popOverlay() {
		Layer *layer = layers.back();
		layers.pop_back();
		return layer;
	}

	void LayerStack::render(bool renderImGui) {
		for (auto &&layer : layers) {
			if (layer->isVisible()) {
				layer->renderBegin();
				layer->render();
				layer->renderEnd();

				if (renderImGui) {
					layer->renderImGui();
				}
			}
		}

		if (Renderer::getClearColor() != color::Transparent) {
			Renderer::instance->setClearColorInternal(color::decode(Renderer::clearColor));
		}

		Renderer::clear(RendererBufferColor | RendererBufferDepth);

		if (Renderer::getClearColor() != color::Transparent) {
			Renderer::instance->setClearColorInternal(color::decode(color::Transparent));
		}

		Renderer::enableBlend(true);
		Renderer::setBlendEquation(BlendEquation::Add);
		Renderer::setBlendFunction(BlendFunction::SourceAlpha, BlendFunction::OneMinusSourceAlpha);

		for (auto &&layer : layers) {
			if (layer->isVisible()) {
				quad->renderTexture(layer->getRenderTexture());
			}
		}
	}

	void LayerStack::tick() {
		for (auto &&layer : layers) {
			if (layer->isVisible()) {
				layer->tick();
			}
		}
	}

	void LayerStack::update(float delta) {
		for (auto &&layer : layers) {
			if (layer->isVisible()) {
				layer->update(delta);
			}
		}
	}

	void LayerStack::lateUpdate(float delta) {
		for (auto &&layer : layers) {
			if (layer->isVisible()) {
				layer->lateUpdate(delta);
			}
		}
	}

	void LayerStack::fixedUpdate(float delta) {
		for (auto &&layer : layers) {
			if (layer->isVisible()) {
				layer->fixedUpdate(delta);
			}
		}
	}

	void LayerStack::input(Event &event) {
		if (event.type == Event::Resized) {
			resize(event.size.width, event.size.height);
		}

		if (!event.handled || event.type == Event::Closed) {
			for (auto it = layers.end(); it != layers.begin();) {
				(*--it)->input(event);
				if (event.handled && event.type != Event::Closed) break;
			}
		}
	}

	void LayerStack::resize(int32 width, int32 height) {
		for (auto &&layer : layers) {
			layer->resize(width, height);
		}
	}

}
