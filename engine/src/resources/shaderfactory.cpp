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


xe::gfx::api::Shader *xe::gfx::sf::batchRendererShader() {
	return api::Shader::createFromSource("BatchRenderer", batchRendererShaderGL);
}

xe::gfx::api::Shader *xe::gfx::sf::basicForwardShader() {
	return api::Shader::createFromSource("BasicForward", basicForwardShaderGL);
}

xe::gfx::api::Shader *xe::gfx::sf::forwardAmbientShader() {
	return api::Shader::createFromSource("ForwardAmbient", forwardAmbientShaderGL);
}