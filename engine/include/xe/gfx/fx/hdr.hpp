//
// Created by FLXR on 9/1/2018.
//

#ifndef X808_HDR_HPP
#define X808_HDR_HPP


#include <xe/common.hpp>
#include <xe/gfx/texture.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/storagebuffer.hpp>
#include <xe/gfx/fx/quad.hpp>
#include <xe/gfx/fx/rendereffect.hpp>

namespace xe { namespace fx {

	class XE_API HDR : public RenderEffect {
	public:
		explicit HDR(uint width, uint height);
		~HDR() override;

		void calcExposure(const Texture *sceneTexture);

		void scaleScene(Quad *quad, const FrameBuffer *sceneFBO, const Texture *sceneTexture);

	private:
		void createTextures();
		void createShaders();

		void luminosity(const Texture *sceneTexture);

		void autoExposure();

	private:
		uint aeSampler0;
		uint ssSampler0;

		const Shader *luminosityShader;
		const Shader *autoExposureShader;
		const Shader *scaleSceneShader;

		Texture *luminosityTexture;
		Texture *tempScene;

		StorageBuffer *exposureSB;
	};

}}


#endif //X808_HDR_HPP
