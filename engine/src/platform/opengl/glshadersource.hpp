//
// Created by FLXR on 7/22/2018.
//

#ifndef X808_GLSHADERSOURCE_HPP
#define X808_GLSHADERSOURCE_HPP


namespace xe {	namespace internal {

		//batch renderer
		static const char *brVertGL =
		#include "shaders/batchrenderer.vert"
				;

		static const char *brFragGL =
		#include "shaders/batchrenderer.frag"
				;

		//lights
		static const char *forwardLightingVertGL =
		#include "shaders/forward-lighting.vert"
				;

		static const char *forwardLightingFragGL =
		#include "shaders/forward-lighting.frag"
				;

		static const char *forwardLightingFragIncludeGL =
		#include "shaders/forward-lighting.frag.include"
				;

		static const char *forwardDirectionalIncludeGL =
		#include "shaders/forward-directionalLight.include"
				;

		static const char *forwardPointIncludeGL =
		#include "shaders/forward-pointLight.include"
				;

		static const char *forwardSpotIncludeGL =
		#include "shaders/forward-spotLight.include"
				;

		static const char *forwardAmbientVertGL =
		#include "shaders/forward-ambientlight.vert"
				;

		static const char *forwardAmbientFragGL =
		#include "shaders/forward-ambientlight.frag"
				;

		//fx
		static const char *fxVertGL =
		#include "shaders/fx/fx.vert"
				;

		static const char *fxNULLFragGL =
		#include "shaders/fx/fx-null.frag"
				;

		static const char *fxGaussBlur7x1FragGL =
		#include "shaders/fx/fx-gaussblur7x1.frag"
				;

		static const char *fxFXAAFragGL =
		#include "shaders/fx/fx-fxaa.frag"
				;

		//shadow map
		static const char *shadowMapVertGL =
		#include "shaders/shadowmap.vert"
				;

		static const char *shadowMapFragGL =
		#include "shaders/shadowmap.frag"
				;

		//include
		static const char *samplingGL =
		#include "shaders/sampling.include"
				;

}}


#endif //X808_GLSHADERSOURCE_HPP
