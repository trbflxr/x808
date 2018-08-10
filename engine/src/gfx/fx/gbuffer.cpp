//
// Created by FLXR on 8/9/2018.
//

#include "gbuffer.hpp"

namespace xe { namespace fx {

	GBuffer::GBuffer(uint width, uint height) :
			RenderEffect(width, height) { }

	void GBuffer::load() {
		loadPrograms();
		loadBuffers();
	}

	void GBuffer::loadPrograms() {

	}

	void GBuffer::loadBuffers() {

	}

	void GBuffer::toggleWireframe() {

	}


}}