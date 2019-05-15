//
// Created by FLXR on 2/8/2019.
//

#include "layerstack.hpp"

namespace xe {

  LayerStack::LayerStack(Application *app) :
      app(*app),
      index(0) { }

  LayerStack::~LayerStack() {
//		for (const auto &l : layers) {
//			delete l;
//		}
  }

  void LayerStack::pushLayer(Layer *layer) {
    layers.emplace(layers.begin() + index, layer);
    ++index;
  }

  Layer *LayerStack::popLayer() {
    --index;
    Layer *layer = layers[index];
    layers.erase(layers.begin() + index);
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
        layer->render();

        if (renderImGui) {
          layer->renderImGui();
        }
      }
    }
  }

  void LayerStack::update(float delta) {
    for (auto &&layer : layers) {
      if (layer->isActive()) {
        layer->update(delta);
      }
    }
  }

  void LayerStack::lateUpdate(float delta) {
    for (auto &&layer : layers) {
      if (layer->isActive()) {
        layer->lateUpdate(delta);
      }
    }
  }

  void LayerStack::fixedUpdate(float delta) {
    for (auto &&layer : layers) {
      if (layer->isActive()) {
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
        if ((*--it)->isActive()) {
          (*it)->input(event);
          if (event.handled && event.type != Event::Closed) break;
        }
      }
    }
  }

  void LayerStack::resize(int32 width, int32 height) {
    for (auto &&layer : layers) {
      layer->resize(width, height);
    }
  }

}
