//
// Created by FLXR on 9/6/2018.
//

#include <xe/gfx/renderer.hpp>
#include <xe/gfx/2d/spriterenderer.hpp>

namespace xe {

	SpriteRenderer::SpriteRenderer(uint width, uint height, bool useLights) :
			IRenderer2D(width, height),
			useLights(useLights) {

		shader = new Shader(useLights ? "dSpriteRendererLighting" : "dSpriteRenderer");

		if (useLights) {
			static constexpr uint lightBlockLocation = 0;

			//bind uniform
			shader->bindUniformBlock("LightBlock", lightBlockLocation);

			BufferLayout l;
			l.push<vec2>("position");
			l.push<float>("offset01", 2);
			l.push<vec4>("color-intensity");

			lightBuffer = new UniformBuffer(BufferStorage::Dynamic, lightBlockLocation, l, MAX_LIGHTS);
		}
	}

	SpriteRenderer::~SpriteRenderer() {
		if (useLights) {
			delete lightBuffer;
		}
	}

	void SpriteRenderer::addLight(Light2D *light) {
		if (lights.size() == MAX_LIGHTS) {
			XE_ERROR("[SpriteRenderer]: can't add light '", light->getName(), "'. Max lights: ", MAX_LIGHTS);
			return;
		}

		lights.push_back(light);
	}

	void SpriteRenderer::updateLightsUBO() {
		for (uint i = 0; i < lights.size(); ++i) {
			lightBuffer->update(&lights[i]->getPosition(), 0, i);

			const vec4 ci(lights[i]->getColor(), lights[i]->getIntensity());
			lightBuffer->update(&ci, 2, i);
		}
	}

	void SpriteRenderer::begin() {
		Renderer::setViewport(0, 0, width, height);

		vertexArray->bind();
		buffer = static_cast<VertexData *>(vertexArray->getBuffer(0)->getPointer());
	}

	void SpriteRenderer::end() {
		Renderer::enableDepthTesting(true);

		std::sort(targets.begin(), targets.end(),
		          [](const RenderTarget a, const RenderTarget b) {
			          return a.sprite->texture > b.sprite->texture;
		          });

		for (auto &&target : targets) {
			submitInternal(target);
		}
		targets.clear();

		//draw transparent
		if (!transparentTargets.empty()) {
			//todo: there must be a better solution
			std::sort(transparentTargets.begin(), transparentTargets.end(),
			          [](const RenderTarget a, const RenderTarget b) {
				          return a.transform->zIndex < b.transform->zIndex;
			          });

			Renderer::enableBlend(true);
			Renderer::setBlendFunction(BlendFunction::SourceAlpha, BlendFunction::OneMinusSourceAlpha);

			for (auto &&target : transparentTargets) {
				submitInternal(target);
			}
			transparentTargets.clear();
		}

		releaseBuffer();
	}

	void SpriteRenderer::flush() {
		shader->bind();

		if (useLights) {
			updateLightsUBO();
			int32 size = static_cast<int32>(lights.size());
			shader->setUniform("lightCount", &size, sizeof(int32));
		}

		shader->updateUniforms();

		for (uint i = 0; i < textures.size(); i++) {
			textures[i]->bind(i);
		}

		vertexArray->bind();
		indexBuffer->bind();

		vertexArray->drawElements(indexCount, BeginMode::Triangles);

		indexBuffer->unbind();
		vertexArray->unbind();

		for (uint i = 0; i < textures.size(); i++) {
			textures[i]->unbind(i);
		}

		shader->unbind();

		indexCount = 0;
		textures.clear();

		//increment draw calls
		Renderer::incDC();
	}

	void SpriteRenderer::submit(const SpriteComponent *sprite, const Transform2DComponent *transform) {
		if (!sprite->visible) return;

		if (sprite->hasTransparency) {
			transparentTargets.emplace_back(sprite, transform);
		} else {
			targets.emplace_back(sprite, transform);
		}
	}

	void SpriteRenderer::submitInternal(const RenderTarget &target) {
		const std::array<vec2, 4> &vertices = target.transform->bounds.getVertices();
		const uint color = target.sprite->color;
		const std::array<vec2, 4> &uv = target.sprite->UVs;
		const Texture *texture = target.sprite->texture;

		float textureSlot = 0.0f;
		if (texture) {
			textureSlot = submitTexture(texture);
		}

		buffer->vertex = mat4::translateVec(*transformationBack, vertices[0], target.transform->zIndex);
		buffer->uv = uv[0];
		buffer->tid = textureSlot;
		buffer->color = color;
		buffer++;

		buffer->vertex = mat4::translateVec(*transformationBack, vertices[3], target.transform->zIndex);
		buffer->uv = uv[1];
		buffer->tid = textureSlot;
		buffer->color = color;
		buffer++;

		buffer->vertex = mat4::translateVec(*transformationBack, vertices[2], target.transform->zIndex);
		buffer->uv = uv[2];
		buffer->tid = textureSlot;
		buffer->color = color;
		buffer++;

		buffer->vertex = mat4::translateVec(*transformationBack, vertices[1], target.transform->zIndex);
		buffer->uv = uv[3];
		buffer->tid = textureSlot;
		buffer->color = color;
		buffer++;

		indexCount += 6;
	}

}
