//
// Created by FLXR on 7/2/2018.
//

#include <xe/gfx/layers/layer2d.hpp>
#include <xe/app/application.hpp>

namespace xe {

	Layer2D::Layer2D() {
		renderer = new Renderer2D(window.getSize());
	}

	Layer2D::~Layer2D() {
		delete renderer;
	}

	bool Layer2D::resize(uint width, uint height) {
		renderer->setScreenSize({width, height});
		return false;
	}

}

