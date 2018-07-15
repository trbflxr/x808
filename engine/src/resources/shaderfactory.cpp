//
// Created by FLXR on 7/4/2018.
//

#include "shaderfactory.hpp"

static const char *batchRendererShaderGL =
#include "platform/opengl/shaders/batchrenderer.shader"
		;

static const char *basicForwardShaderGL =
#include "platform/opengl/shaders/basicforward.shader"
		;

static const char *forwardAmbientShaderGL =
#include "platform/opengl/shaders/forwardambient.shader"
		;

namespace xe {

	gfx::api::Shader *gfx::sf::batchRendererShader() {
		return api::Shader::createFromSource("BatchRenderer", batchRendererShaderGL);
	}

	gfx::api::Shader *gfx::sf::basicForwardShader() {
		return api::Shader::createFromSource("BasicForward", basicForwardShaderGL);
	}

	gfx::api::Shader *gfx::sf::forwardAmbientShader() {
		return api::Shader::createFromSource("ForwardAmbient", forwardAmbientShaderGL);
	}

}