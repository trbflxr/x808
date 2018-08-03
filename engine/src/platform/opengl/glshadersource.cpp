//
// Created by FLXR on 7/22/2018.
//

#include "glshaderresource.hpp"

static const char *batchRendererShaderGL =
#include "shaders/batchrenderer.shader"
		;

static const char *forwardAmbientShaderGL =
#include "shaders/forward-ambient.fs"
		;

static const char *forwardAmbientVertGL =
#include "shaders/ambient-light.vsh"
		;

static const char *forwardAmbientFragGL =
#include "shaders/ambient-light.fsh"
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

static const char *lightingMainGL =
#include "shaders/lightingMain.fsh"
		;

static const char *lightingVertGL =
#include "shaders/lighting.vsh"
		;

static const char *lightingFragGL =
#include "shaders/lighting.fsh"
		;

static const char *lightingSrcGL =
#include "shaders/lighting.glh"
		;

static const char *samplingSrcGL =
#include "shaders/sampling.glh"
		;

static const char *shadowMapSrcGL =
#include "shaders/shadowmap-generator.shader"
		;

static const char *filterGaussBlurGL =
#include "shaders/filter-gausblur7x1.shader"
		;

static const char *filterFXAAGL =
#include "shaders/filter-fxaa.shader"
		;

namespace xe { namespace gfx {

	std::string batchRendererShaderSourceGL() {
		return batchRendererShaderGL;
	}

	std::string forwardAmbientShaderSourceGL() {
		std::string src;
		src += forwardAmbientVertGL;
		src += forwardAmbientFragGL;
		src += samplingSrcGL;
		src += forwardAmbientShaderGL;

		return src;
	}

	std::string forwardDirectionalShaderSourceGL() {
		std::string src;
		src += lightingVertGL;
		src += lightingFragGL;
		src += lightingSrcGL;
		src += forwardDirectionalShaderGL;
		src += samplingSrcGL;
		src += lightingMainGL;

		return src;
	}

	std::string forwardPointShaderSourceGL() {
		std::string src;
		src += lightingVertGL;
		src += lightingFragGL;
		src += lightingSrcGL;
		src += forwardPointShaderGL;
		src += samplingSrcGL;
		src += lightingMainGL;

		return src;
	}

	std::string forwardSpotShaderSourceGL() {
		std::string src;
		src += lightingVertGL;
		src += lightingFragGL;
		src += lightingSrcGL;
		src += forwardSpotShaderGL;
		src += samplingSrcGL;
		src += lightingMainGL;

		return src;
	}

	std::string shadowMapSourceGL() {
		return shadowMapSrcGL;
	}

	std::string filterGaussBlurSourceGL() {
		return filterGaussBlurGL;
	}

	std::string filterFXAASourceGL() {
		return filterFXAAGL;
	}

}}