//
// Created by FLXR on 8/4/2018.
//

#include <xe/gfx/renderer.hpp>
#include <xe/gfx/deferredrenderer.hpp>

namespace xe {

	DeferredRenderer::DeferredRenderer(uint width, uint height) {
		BufferLayout cl;
		cl.push<mat4>("view");
		cl.push<mat4>("perspective");
		cl.push<vec3>("camPosition");
		cl.push<vec3>("camLook");

		cameraUBO = new UniformBuffer(BufferStorage::Dynamic, 1, cl);

		//init fx
		quad = new fx::Quad(width, height);
		final = new fx::Final(width, height, false);
		gBuffer = new fx::GBuffer(width, height);
	}

	DeferredRenderer::~DeferredRenderer() {
		delete cameraUBO;

		delete quad;
		delete final;
		delete gBuffer;
	}

	void DeferredRenderer::updateUBO(const mat4 &view, const mat4 &proj, const vec3 &pos, const vec3 &look) const {
		cameraUBO->update(&view, 0);
		cameraUBO->update(&proj, 1);
		cameraUBO->update(&pos, 2);
		cameraUBO->update(&look, 3);
	}

	void DeferredRenderer::render(const Scene *scene, Camera *camera) const {
		const vec3 look = camera->transform.getRotation().getForward();
		const vec3 pos = -camera->transform.getPosition();
		const mat4 view = camera->getView();
		const mat4 proj = camera->getProjection();

		updateUBO(view, proj, pos, look);

		Renderer::enableDepthTesting(false);


		//render
		Renderer::enableDepthMask(true);
		Renderer::enableDepthTesting(true);
		Renderer::enableCullFace(true);
		Renderer::setCullFace(CullFace::Back);

		gBuffer->passDeferredShading(scene);

		Renderer::enableDepthTesting(false);
		gBuffer->passLightAccumulation(quad, final->getFinalFBO());

		final->render(quad);
	}

}