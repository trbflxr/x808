//
// Created by FLXR on 9/6/2018.
//

#include <algorithm>
#include <xe/gfx/renderer.hpp>
#include <xe/gfx/2d/renderer2d.hpp>

namespace xe {

	Renderer2D::Renderer2D(uint width, uint height, Camera *camera) :
			IRenderer2D(width, height, camera) {

		shader = new Shader("dRenderer2D");
	}

	void Renderer2D::begin() {
		Renderer::enableBlend(true);
		Renderer::setBlendFunction(BlendFunction::SourceAlpha, BlendFunction::OneMinusSourceAlpha);
		Renderer::setViewport(0, 0, width, height);

		vertexArray->bind();
		buffer = static_cast<VertexData *>(vertexArray->getBuffer(0)->getPointer());
	}

	void Renderer2D::end() {
		updateCamera();

		Renderer::enableDepthTesting(true);

		std::sort(targets.begin(), targets.end(),
		          [](const IRenderable2D *a, const IRenderable2D *b) {
			          return a->getTexture() > b->getTexture();
		          });

		for (auto &&target : targets) {
			submitInternal(target);
		}
		targets.clear();

		//draw transparent
		if (!transparentTargets.empty()) {
			//todo: there must be a better solution
			std::sort(transparentTargets.begin(), transparentTargets.end(),
			          [](const IRenderable2D *a, const IRenderable2D *b) {
				          return a->getZ() < b->getZ();
			          });

			for (auto &&target : transparentTargets) {
				submitInternal(target);
			}
			transparentTargets.clear();
		}

		releaseBuffer();
	}

	void Renderer2D::flush() {
		updateIndexBuffer();

		shader->bind();
		shader->updateUniforms();

		for (uint i = 0; i < textures.size(); i++) {
			textures[i]->bind(i);
		}

		vertexArray->bind();
		indexBuffer->bind();

		vertexArray->drawElements(indicesSize, BeginMode::Triangles);

		indexBuffer->unbind();
		vertexArray->unbind();

		for (uint i = 0; i < textures.size(); i++) {
			textures[i]->unbind(i);
		}

		shader->unbind();

		indicesSize = 0;
		indicesOffset = 0;

		textures.clear();

		//increment draw calls
		Renderer::incDC();
	}

	void Renderer2D::render(const std::vector<const IRenderable2D *> &targets) {
		begin();

		for (const auto &t: targets) {
			submitInternal(t);
		}

		releaseBuffer();
		flush();
	}

	void Renderer2D::submit(const IRenderable2D *target) {
		if (!target->isVisible()) return;

		const Texture *texture = target->getTexture();

		if (texture && texture->hasTransparency()) {
			transparentTargets.push_back(target);
		} else {
			targets.push_back(target);
		}
	}

	void Renderer2D::submitInternal(const IRenderable2D *target) {
		const Vertex2D *vertices = target->getVertices();
		const uint color = target->getColor();
		const Texture *texture = target->getTexture();

		const mat4 transform = *transformationBack * target->getTransformation();

		float textureSlot = 0.0f;
		if (texture) {
			textureSlot = submitTexture(texture);
		}

		appendIndices(target->getIndices(), target->getIndicesCount(), target->getPointCount());

		uint ti = target->getPointCount() - 1;
		for (uint i = 0; i < target->getPointCount(); ++i) {
			buffer->vertex = transform * vertices[i].pos;
			buffer->uv = vertices[ti--].uv;
			buffer->tid = textureSlot;
			buffer->color = color;
			buffer++;
		}
	}

}
