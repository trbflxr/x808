//
// Created by FLXR on 3/6/2019.
//

#include <xe/gfx/shadows.hpp>
#include <xe/gfx/scene.hpp>
#include <xe/gfx/camera.hpp>
#include <xe/resources/shadermanager.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe {

	Shadows::Shadows(ShadowParameters params) :
			params(params),
			spotShadowsIndex(0) {

		createTextures();
		createBuffers();
		createShaders();
	}

	Shadows::~Shadows() {
		delete spotBuffer;
		delete spotUBO;
		delete spotTexture;
		delete spotDepthTexture;

		delete dirBuffer;
		delete dirUBO;
		delete dirTexture;
		delete dirDepthTexture;
	}

	void Shadows::createTextures() {
		TextureParameters tp(TextureTarget::Tex2DArray);
		tp.internalFormat = PixelInternalFormat::Rg16f;
		tp.format = PixelFormat::Rg;
		tp.pixelType = PixelType::Float;
		tp.magFilter = TextureMagFilter::Linear;
		tp.minFilter = TextureMinFilter::Linear;
		tp.wrap = TextureWrap::Clamp;

		spotTexture = new Texture("ST", params.spotSize, params.spotSize, params.maxSpotCount, tp);
		dirTexture = new Texture("DT", params.dirSize, params.dirSize, params.dirCascades, tp);

		tp.internalFormat = PixelInternalFormat::DepthComponent16;
		tp.format = PixelFormat::DepthComponent;
		spotDepthTexture = new Texture("SDT", params.spotSize, params.spotSize, params.maxSpotCount, tp);
		dirDepthTexture = new Texture("DDT", params.dirSize, params.dirSize, params.dirCascades, tp);
	}

	void Shadows::createBuffers() {
		//fbo's
		spotBuffer = new FrameBuffer("SB");
		spotBuffer->load({std::make_pair(Attachment::Depth, spotDepthTexture),
		                  std::make_pair(Attachment::Color0, spotTexture)});

		dirBuffer = new FrameBuffer("DB");
		dirBuffer->load({std::make_pair(Attachment::Depth, dirDepthTexture),
		                 std::make_pair(Attachment::Color0, dirTexture)});

		//ubo's
		BufferLayout sl;
		sl.push<mat4>("view");
		sl.push<mat4>("projection");
		spotUBO = new UniformBuffer(BufferStorage::Dynamic, 2, sl, params.maxSpotCount);

		BufferLayout dl;
		dl.push<mat4>("view");
		for (uint i = 0; i < params.dirCascades; ++i) {
			dl.push<mat4>("projection");
		}
		dirUBO = new UniformBuffer(BufferStorage::Dynamic, 4, dl);

	}

	void Shadows::createShaders() {
		spotShader = GETSHADER("dSpotShadows");
		spotShader->bindUniformBlock("SpotShadows", 2);

		dirShader = GETSHADER("dDirectionalShadows");
		dirShader->bindUniformBlock("DirectionalShadows", 4);
	}

	void Shadows::render(const Scene *scene, const Camera *camera) {
		renderSpotShadows(scene);
		renderDirectionalShadows(scene, camera);
	}

	void Shadows::renderSpotShadows(const Scene *scene) {
		spotShadowsIndex = 0;
		spotUBO->bind();
		for (const auto &light : scene->getSpotLights()) {
			if (!light->isShadowed() || (uint) spotShadowsIndex - 1 == params.maxSpotCount) {
				light->setShadowId(-1);
				continue;
			}

			spotUBO->update(&light->getView(), 0, spotShadowsIndex);
			spotUBO->update(&light->getProjection(), 1, spotShadowsIndex);

			light->setShadowId(spotShadowsIndex);
			++spotShadowsIndex;
		}
		spotUBO->unbind();
		renderScene(scene, spotShader, spotBuffer, spotShadowsIndex, params.spotSize);
	}

	void Shadows::renderDirectionalShadows(const Scene *scene, const Camera *camera) {
		DirectionalLight *light = const_cast<DirectionalLight *>(scene->getDirectionalLight());
		if (!light || !light->isShadowed()) return;

		dirUBO->bind();
		const std::vector<mat4> &projection = light->getProjection();

		light->setPosition(camera->getPosition());

		dirUBO->update(&light->getView(), 0);
		for (uint i = 0; i < projection.size(); ++i) {
			dirUBO->update(&projection[i], i + 1); //1st - view matrix
		}

		dirUBO->unbind();
		renderScene(scene, dirShader, dirBuffer, projection.size(), params.dirSize);
	}

	void Shadows::renderScene(const Scene *scene, const Shader *shader,
	                          const FrameBuffer *buffer, uint count, uint size) {

		Renderer::enableBlend(false);
		Renderer::enableDepthTesting(true);
		Renderer::enableDepthMask(true);
		Renderer::enableCullFace(true);
		Renderer::setCullFace(CullFace::Back);

		buffer->bindDraw(Attachment::Color0);
		Renderer::setViewport(0, 0, size, size);
		Renderer::clear(RendererBufferColor | RendererBufferDepth);

		shader->bind();

		for (const auto &m : scene->getModels()) {
			shader->setUniform("model", &m->toMatrix(), sizeof(mat4));
			shader->updateUniforms();

			m->renderInstanced(BeginMode::Triangles, count);
		}

		shader->unbind();

		buffer->unbind();
	}
}
