//
// Created by FLXR on 8/4/2018.
//

#include "deferredrenderer.hpp"

namespace xe {

	DeferredRenderer::DeferredRenderer(uint width, uint height, Camera *camera) :
			IRenderer3D(width, height, camera) {

	}

	DeferredRenderer::~DeferredRenderer() {

	}

	void DeferredRenderer::begin() {

	}

	void DeferredRenderer::submit(const Mesh *mesh, const Material *material, const Transform &transform) {

	}

	void DeferredRenderer::flush() {

	}


}