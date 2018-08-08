//
// Created by FLXR on 7/22/2018.
//

#ifndef X808_GLSHADERSOURCE_HPP
#define X808_GLSHADERSOURCE_HPP


namespace xe {	namespace internal {

		//batch renderer
		static const char *brVertGL =
		#include "shaders/.old/batchrenderer.vert"
				;

		static const char *brFragGL =
		#include "shaders/.old/batchrenderer.frag"
				;

		//lights
		static const char *forwardLightingVertGL =
		#include "shaders/.old/forward-lighting.vert"
				;

		static const char *forwardLightingFragGL =
		#include "shaders/.old/forward-lighting.frag"
				;

		static const char *forwardLightingFragIncludeGL =
		#include "shaders/.old/forward-lighting.frag.include"
				;

		static const char *forwardDirectionalIncludeGL =
		#include "shaders/.old/forward-directionalLight.include"
				;

		static const char *forwardPointIncludeGL =
		#include "shaders/.old/forward-pointLight.include"
				;

		static const char *forwardSpotIncludeGL =
		#include "shaders/.old/forward-spotLight.include"
				;

		static const char *forwardAmbientVertGL =
		#include "shaders/.old/forward-ambientlight.vert"
				;

		static const char *forwardAmbientFragGL =
		#include "shaders/.old/forward-ambientlight.frag"
				;

		//fx
		static const char *fxVertGL =
		#include "shaders/.old/fx/fx.vert"
				;

		static const char *fxNULLFragGL =
		#include "shaders/.old/fx/fx-null.frag"
				;

		static const char *fxGaussBlur7x1FragGL =
		#include "shaders/.old/fx/fx-gaussblur7x1.frag"
				;

		static const char *fxFXAAFragGL =
		#include "shaders/.old/fx/fx-fxaa.frag"
				;

		//shadow map
		static const char *shadowMapVertGL =
		#include "shaders/.old/shadowmap.vert"
				;

		static const char *shadowMapFragGL =
		#include "shaders/.old/shadowmap.frag"
				;

		//include
		static const char *samplingGL =
		#include "shaders/.old/sampling.include"
				;



		/////////////////////////////
		/// new
		////////////////////////////

		//deferred
		//ubo
		static const char *cameraSpatialsGL =
		#include "shaders/common/ubo/cameraSpatials.ubo"
				;

		//include
		static const char *fxaaIncludeGL =
		#include "shaders/common/include/fxaa.include"
				;

		///----- common -----///
		//vert
		static const char *commonGenericFXVertGL =
		#include "shaders/common/renderTexture2D.vert"
				;

		static const char *renderTextureCubeVertGL =
		#include "shaders/common/renderTextureCube.vert"
				;

		//frag
		static const char *renderTexture1DFragGL =
		#include "shaders/common/renderTexture1D.frag"
				;

		static const char *renderTexture2DFragGL =
		#include "shaders/common/renderTexture2D.frag"
				;

		static const char *renderTexture2DArrayFragGL =
		#include "shaders/common/renderTexture2DArray.frag"
				;

		static const char *renderTexture3DFragGL =
		#include "shaders/common/renderTexture3D.frag"
				;

		static const char *renderTextureCubeFragGL =
		#include "shaders/common/renderTextureCube.frag"
				;

		static const char *renderTextureCubeArrayFragGL =
		#include "shaders/common/renderTextureCubeArray.frag"
				;

		///----- fx -----///
		//final
		static const char *finalSceneFragGL =
		#include "shaders/final/finalScene.frag"
				;

}}


#endif //X808_GLSHADERSOURCE_HPP
