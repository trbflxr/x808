//
// Created by FLXR on 7/22/2018.
//

#ifndef X808_GLSHADERSOURCE_HPP
#define X808_GLSHADERSOURCE_HPP


namespace xe {	namespace internal {

		//batch renderer
		static const char *brVertGL =
		#include "shaders/batchRenderer.vert"
				;

		static const char *brFragGL =
		#include "shaders/batchRenderer.frag"
				;

		//lights
		static const char *forwardLightingVertGL =
		#include "shaders/forwardLighting.vert"
				;

		static const char *forwardLightingFragGL =
		#include "shaders/forwardLighting.frag"
				;

		static const char *forwardLightingFragIncludeGL =
		#include "shaders/include/forwardLighting.frag.include"
				;

		static const char *forwardDirectionalIncludeGL =
		#include "shaders/include/forwardDirectionalLight.include"
				;

		static const char *forwardPointIncludeGL =
		#include "shaders/include/forwardPointLight.include"
				;

		static const char *forwardSpotIncludeGL =
		#include "shaders/include/forwardSpotLight.include"
				;

		static const char *forwardAmbientVertGL =
		#include "shaders/forwardAmbientlight.vert"
				;

		static const char *forwardAmbientFragGL =
		#include "shaders/forwardAmbientlight.frag"
				;

		//shadow map
		static const char *shadowMapVertGL =
		#include "shaders/shadowMap.vert"
				;

		static const char *shadowMapFragGL =
		#include "shaders/shadowMap.frag"
				;

		//include
		static const char *samplingGL =
		#include "shaders/include/sampling.include"
				;



		///----- common -----///
		static const char *commonGenericVertGL =
		#include "shaders/common/commonGeneric.vert"
				;

		///----- include -----///
		static const char *fxaaIncludeGL =
		#include "shaders/include/fxaa.include"
				;

		///----- fx -----///
		//final
		static const char *finalSceneFragGL =
		#include "shaders/final/finalScene.frag"
				;

		//blur
		static const char *fxGaussBlur7x1FragGL =
		#include "shaders/fx/gaussBlur7x1.frag"
				;

}}


#endif //X808_GLSHADERSOURCE_HPP
