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

static const char *forwardDirectionalShaderGL =
#include "platform/opengl/shaders/forwarddirectional.shader"
		;

static const char *forwardPointShaderGL =
#include "platform/opengl/shaders/forwardpoint.shader"
		;

namespace xe { namespace gfx { namespace sf {

	api::Shader *batchRendererShader() {
		return api::Shader::createFromSource("BatchRenderer", batchRendererShaderGL);
	}

	api::Shader *basicForwardShader() {
		return api::Shader::createFromSource("BasicForward", basicForwardShaderGL);
	}

	api::Shader *forwardAmbientShader() {
		return api::Shader::createFromSource("ForwardAmbient", forwardAmbientShaderGL);
	}

	api::Shader *forwardDirectionalShader() {
		return api::Shader::createFromSource("ForwardDirectional", forwardDirectionalShaderGL);
	}

	api::Shader *forwardPointShader() {
		return api::Shader::createFromSource("ForwardPoint", forwardPointShaderGL);
	}

}}}