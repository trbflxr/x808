//
// Created by FLXR on 7/12/2018.
//

#ifndef X808_FORWARDRENDERER_HPP
#define X808_FORWARDRENDERER_HPP


#include "gfx/api/framebuffer.hpp"
#include "gfx/camera.hpp"
#include "gfx/lights/ambientlight.hpp"
#include "gfx/forwardrenderershader.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "math/transform.hpp"

namespace xe { namespace gfx {

	class XE_API ForwardRenderer {
	private:
		struct RenderTarget {
			const Mesh *mesh;
			const Material *material;
			const Transform &transform;

			RenderTarget(const Mesh *mesh, const Material *material, const Transform &transform) noexcept :
					mesh(mesh), material(material), transform(transform) { }
		};

	public:
		explicit ForwardRenderer(uint width, uint height, Camera *camera, bool useFXAA = false);
		~ForwardRenderer();

		inline void addLight(BaseLight *light) { lights.push_back(light); }

		void begin();
		void submit(const Mesh *mesh, const Material *material, const Transform &transform);
		void flush();

		inline const Camera *getCamera() const { return camera; }
		inline Camera *getCamera() { return camera; }

		inline void setCamera(Camera *camera) { ForwardRenderer::camera = camera; }

		inline AmbientLight *getAmbientLight() { return ambientLight; }
		inline const AmbientLight *getAmbientLight() const { return ambientLight; }

	private:
		uint renderShadows(BaseLight *light);

		void blurShadowMap(uint index, float blurAmount);
		void applyFilter(ForwardRendererShader *filter, api::FrameBuffer *src, api::FrameBuffer *dest);

	private:
		std::vector<RenderTarget> targets;
		std::vector<BaseLight *> lights;

		uint width;
		uint height;

		Camera *camera;

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

}}


#endif //X808_FORWARDRENDERER_HPP
