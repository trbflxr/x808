//
// Created by FLXR on 7/22/2018.
//

#include <string>

#include <utils/log.hpp>
#include "glshaderresource.hpp"

static const char *batchRendererShaderGL =
#include "shaders/batchrenderer.shader"
		;

static const char *basicForwardShaderGL =
#include "shaders/basicforward.shader"
		;

static const char *forwardAmbientShaderGL =
#include "shaders/forward-ambient.shader"
		;

static const char *forwardDirectionalShaderGL =
#include "shaders/forward-directional.fs"
		;

static const char *forwardPointShaderGL =
#include "shaders/forward-point.fs"
		;

static const char *forwardSpotShaderGL =
#include "shaders/forward-spot.fs"
		;

static const char *lightingMain =
#include "shaders/lightingMain.fsh"
		;

static const char *lightingVert =
#include "shaders/lighting.vsh"
		;

static const char *lightingFrag =
#include "shaders/lighting.fsh"
		;

static const char *lightingSrc =
#include "shaders/lighting.glh"
		;

namespace xe { namespace gfx {

	std::string batchRendererShaderSourceGL() {
		return batchRendererShaderGL;
	}

	std::string basicForwardShaderSourceGL() {
		return basicForwardShaderGL;
	}

	std::string forwardAmbientShaderSourceGL() {
		return forwardAmbientShaderGL;
	}

	std::string forwardDirectionalShaderSourceGL() {
		std::string src;
		src += lightingVert;
		src += lightingFrag;
		src += lightingSrc;
		src += forwardDirectionalShaderGL;
		src += lightingMain;

		return src;
	}

	std::string forwardPointShaderSourceGL() {
		std::string src;
		src += lightingVert;
		src += lightingFrag;
		src += lightingSrc;
		src += forwardPointShaderGL;
		src += lightingMain;

		return src;
	}

	std::string forwardSpotShaderSourceGL() {
		std::string src;
		src += lightingVert;
		src += lightingFrag;
		src += lightingSrc;
		src += forwardSpotShaderGL;
		src += lightingMain;

		return src;
	}

}}