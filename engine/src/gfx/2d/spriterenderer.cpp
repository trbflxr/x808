//
// Created by FLXR on 9/6/2018.
//

#include <algorithm>
#include <xe/gfx/renderer.hpp>
#include <xe/gfx/2d/spriterenderer.hpp>

namespace xe {

	SpriteRenderer::SpriteRenderer(uint width, uint height, Camera *camera) :
			IRenderer2D(width, height, camera) {

		shader = new Shader("dSpriteRenderer");
	}

	void SpriteRenderer::begin() {
		Renderer::enableBlend(true);
		Renderer::setBlendFunction(BlendFunction::SourceAlpha, BlendFunction::OneMinusSourceAlpha);
		Renderer::setViewport(0, 0, width, height);

		vertexArray->bind();
		buffer = static_cast<VertexData *>(vertexArray->getBuffer(0)->getPointer());
	}

	void SpriteRenderer::end() {
		updateCamera();

		Renderer::enableDepthTesting(true);

		std::sort(targets.begin(), targets.end(),
		          [](const Sprite *a, const Sprite *b) {
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
			          [](const Sprite *a, const Sprite *b) {
				          return a->getPosition().z < b->getPosition().z;
			          });

			for (auto &&target : transparentTargets) {
				submitInternal(target);
			}
			transparentTargets.clear();
		}

		releaseBuffer();
	}

	void SpriteRenderer::flush() {
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

	void SpriteRenderer::render(const std::vector<const Sprite *> &sprites) {
		begin();

		for (const auto &s: sprites) {
			submitInternal(s);
		}

		releaseBuffer();
		flush();
	}

	void SpriteRenderer::submit(const Sprite *sprite) {
		if (!sprite->isVisible()) return;

		if (sprite->hasTransparency()) {
			transparentTargets.push_back(sprite);
		} else {
			targets.push_back(sprite);
		}
	}

	void SpriteRenderer::submitInternal(const Sprite *sprite) {
		const Vertex2D *vertices = sprite->getVertices();
		const uint color = sprite->getColor();
		const Texture *texture = sprite->getTexture();

		float textureSlot = 0.0f;
		if (texture) {
			textureSlot = submitTexture(texture);
		}

		appendIndices(sprite->getIndices(), sprite->getIndicesSize(), sprite->getVerticesSize());

		for (uint i = 0; i < sprite->getVerticesSize(); ++i) {
			buffer->vertex = mat4::translateVec(*transformationBack, vertices[i].pos);
			buffer->uv = vertices[i].uv;
			buffer->tid = textureSlot;
			buffer->color = color;
			buffer++;
		}

//		indexCount += 6;
	}

}
