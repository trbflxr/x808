//
// Created by FLXR on 7/12/2018.
//

#ifndef X808_FORWARDRENDERER_HPP
#define X808_FORWARDRENDERER_HPP


#include "irenderer3d.hpp"
#include "gfx/api/framebuffer.hpp"
#include "gfx/lights/ambientlight.hpp"
#include "gfx/forwardrenderershader.hpp"

namespace xe {

	class XE_API ForwardRenderer : public IRenderer3D {
	public:
		explicit ForwardRenderer(uint width, uint height, Camera *camera, bool useFXAA = false);
		~ForwardRenderer();

		inline void addLight(BaseLight *light) { lights.push_back(light); }

		void begin() override;
		void submit(const Mesh *mesh, const Material *material, const Transform &transform) override;
		void flush() override;

		inline AmbientLight *getAmbientLight() { return ambientLight; }
		inline const AmbientLight *getAmbientLight() const { return ambientLight; }

	private:
		uint renderShadows(BaseLight *light);

		void blurShadowMap(uint index, float blurAmount);
		void applyFilter(ForwardRendererShader *filter, api::FrameBuffer *src, api::FrameBuffer *dest);

	private:
		std::vector<RenderTarget> targets;
		std::vector<BaseLight *> lights;

		AmbientLight *ambientLight;
		ForwardRendererShader *shadowMapShader;
		ForwardRendererShader *shadowMapBlurShader;

		bool useFXAA;
		ForwardRendererShader *fxaaFilter;

		api::FrameBuffer *screenBuffer;

		//shadows stuff
		static constexpr uint NUM_SHADOW_MAPS = 10;

		api::FrameBuffer *shadowBuffers0[NUM_SHADOW_MAPS];
		api::FrameBuffer *shadowBuffers1[NUM_SHADOW_MAPS];

		Camera *lightCamera;
		mat4 lightMatrix;
		float shadowVarianceMin;
		float shadowLightBleedingReduction;

		Mesh *dummyMesh;
		Material *dummyMaterial;
		Transform dummyTransform;
		GameObject dummyGameObject;
	};

}


#endif //X808_FORWARDRENDERER_HPP
