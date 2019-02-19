//
// Created by FLXR on 9/6/2018.
//

#include <algorithm>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/shadermanager.hpp>
#include <xe/gfx/2d/renderer2d.hpp>

namespace xe {

	Renderer2D::Renderer2D(uint width, uint height, Camera *camera, const Shader *customShader) :
			IRenderer2D(width, height, camera),
			enableWireframe_(false) {

		shader = customShader ? customShader : GETSHADER("dRenderer2D");
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
				          return a->getLayer() < b->getLayer();
			          });

			for (auto &&target : transparentTargets) {
				submitInternal(target);
			}
			transparentTargets.clear();
		}

		releaseBuffer();
	}

	void Renderer2D::flush() {
		Renderer::enableDepthTesting(true);

		updateIndexBuffer();

		shader->bind();
		shader->updateUniforms();

		for (uint i = 0; i < textures.size(); i++) {
			textures[i]->bind(i);
		}

		vertexArray->bind();
		indexBuffer->bind();

		if (enableWireframe_) {
			Renderer::setPolygonMode(MaterialFace::FrontAndBack, PolygonMode::Line);
		}

		vertexArray->drawElements(indicesSize, BeginMode::Triangles);

		if (enableWireframe_) {
			Renderer::setPolygonMode(MaterialFace::FrontAndBack, PolygonMode::Fill);
		}

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
			if (t->isVisible()) {
				submitInternal(t);
			}
		}

		releaseBuffer();
		flush();
	}

	void Renderer2D::render(const std::vector<IRenderable2D *> &targets) {
		begin();

		for (const auto &t: targets) {
			if (t->isVisible()) {
				submitInternal(t);
			}
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
		const uint count = target->getPointCount();
		const uint indicesCount = target->getIndicesCount();

		if (count < 3) return;

		const Vertex2D *vertices = target->getVertices();
		const uint color = target->getColor();
		const Texture *texture = target->getTexture();

		const mat4 transform = target->getTransformation() * *transformationBack;

		float textureSlot = 0.0f;
		if (texture) {
			textureSlot = submitTexture(texture);
		}

		appendIndices(target->getIndices(), indicesCount, count);

		for (uint i = 0; i < count; ++i) {
			buffer->vertex = mat4::translateXY(transform, vertices[i].pos);

			//todo: refactor
			if (texture && texture->isFlipped()) {
				buffer->uv = vertices[count - i - 1].uv;
			} else {
				buffer->uv = vertices[i].uv;
			}

			buffer->tid = textureSlot;
			buffer->color = color;
			buffer++;
		}
	}

}
