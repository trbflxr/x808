//
// Created by FLXR on 9/10/2018.
//

#include <algorithm>
#include <xe/gfx/batchrenderer2d.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe {

	BatchRenderer2D::BatchRenderer2D(uint width, uint height, Camera *camera) :
			camera(camera) {

		renderer = new Renderer2D(width, height, camera);
		textRenderer = new TextRenderer(width, height, camera);
	}

	BatchRenderer2D::~BatchRenderer2D() {
		delete renderer;
		delete textRenderer;
	}

	void BatchRenderer2D::submit(const IRenderable2D *target) {
		if (!target->isVisible()) return;

		const Texture *texture = target->getTexture();

		if (texture && texture->getParams().format == PixelFormat::Rgba) {
			transparentTargets.push_back(target);
		} else {
			targets.push_back(target);
		}
	}

	void BatchRenderer2D::submit(const Text *text) {
		BatchRenderer2D::text.push_back(text);
	}

	void BatchRenderer2D::renderSprites() {
		renderer->updateCamera();

		Renderer::enableDepthTesting(true);

		std::sort(targets.begin(), targets.end(),
		          [](const IRenderable2D *a, const IRenderable2D *b) {
			          return a->getTexture() > b->getTexture();
		          });

		renderer->render(targets);
		targets.clear();

		//draw transparent
		if (!transparentTargets.empty()) {
			//todo: there must be a better solution
			std::sort(transparentTargets.begin(), transparentTargets.end(),
			          [](const IRenderable2D *a, const IRenderable2D *b) {
				          return a->getLayer() < b->getLayer();
			          });

			renderer->render(transparentTargets);
			transparentTargets.clear();
		}
	}

	void BatchRenderer2D::renderText() {
		textRenderer->updateCamera();

		Renderer::enableDepthTesting(false);

		textRenderer->render(text);
		text.clear();
	}

	void BatchRenderer2D::clear() {
		transparentTargets.clear();
		targets.clear();
		text.clear();
	}

}