//
// Created by FLXR on 7/12/2018.
//

#ifndef X808_FORWARDRENDERER_HPP
#define X808_FORWARDRENDERER_HPP


#include "irenderer3d.hpp"
#include "gfx/api/framebuffer_old.hpp"
#include "gfx/lights/ambientlight.hpp"
#include "gfx/forwardrenderershader.hpp"
#include "gfx/fx/quad.hpp"
#include "gfx/fx/final.hpp"
#include "gfx/fx/gaussblur7x1.hpp"

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

		//todo: temp. remove
		void input(Event &event);

	private:
		uint renderShadows(BaseLight *light);

		void blurShadowMap(uint index, float blurAmount);

	private:
		std::vector<RenderTarget> targets;
		std::vector<BaseLight *> lights;

		AmbientLight *ambientLight;
		ForwardRendererShader *shadowMapShader;

		bool useFXAA;

		api::FrameBufferOld *screenBuffer;

		//shadows stuff
		static constexpr uint NUM_SHADOW_MAPS = 10;

		api::FrameBufferOld *shadowBuffers0[NUM_SHADOW_MAPS];
		api::FrameBufferOld *shadowBuffers1[NUM_SHADOW_MAPS];

		Camera *lightCamera;
		mat4 lightMatrix;
		float shadowVarianceMin;
		float shadowLightBleedingReduction;

		//fx
		fx::Quad *quad;
		fx::Final *finalFx;
		fx::GaussBlur7x1 *blurFx;
	};

}


#endif //X808_FORWARDRENDERER_HPP
