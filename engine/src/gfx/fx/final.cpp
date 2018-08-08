//
// Created by FLXR on 8/8/2018.
//

#include "final.hpp"
#include "resources/shadermanager.hpp"

namespace xe { namespace fx {

	Final::Final(uint width, uint height) :
			RenderEffect(width, height) {	}

	Final::~Final() {

	}

	void Final::load() {
		loadPrograms();
		loadBuffers();
	}

	void Final::loadPrograms() {
		finalScene = GETSHADER("defaultFinalScene");
	}

	void Final::loadBuffers() {
//		finalTexture = api::Texture::create(width, height, )
	}

	void Final::render(Quad *quad) {

	}

}}
