//
// Created by FLXR on 9/10/2018.
//

#include <algorithm>
#include <xe/gfx/2d/batchrenderer2d.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe {

	BatchRenderer2D::BatchRenderer2D(uint width, uint height, Camera *camera) :
			camera(camera) {

		spriteRenderer = new SpriteRenderer(width, height, camera);
		textRenderer = new TextRenderer(width, height, camera);
	}

	BatchRenderer2D::~BatchRenderer2D() {
		delete spriteRenderer;
		delete textRenderer;
	}

	void BatchRenderer2D::submit(const IRenderable2D *renderable) {
		if (!renderable->isVisible()) return;

		if (renderable->hasTransparency()) {
			transparentSprites.push_back(renderable);
		} else {
			sprites.push_back(renderable);
		}
	}

	void BatchRenderer2D::submit(const Text *text) {
		BatchRenderer2D::text.push_back(text);
	}

	void BatchRenderer2D::renderSprites() {
		spriteRenderer->updateCamera();

		Renderer::enableDepthTesting(true);

		std::sort(sprites.begin(), sprites.end(),
		          [](const IRenderable2D *a, const IRenderable2D *b) {
			          return a->getTexture() > b->getTexture();
		          });

		spriteRenderer->render(sprites);
		sprites.clear();

		//draw transparent
		if (!transparentSprites.empty()) {
			//todo: there must be a better solution
			std::sort(transparentSprites.begin(), transparentSprites.end(),
			          [](const IRenderable2D *a, const IRenderable2D *b) {
				          return a->getPosition().z < b->getPosition().z;
			          });

			spriteRenderer->render(transparentSprites);
			transparentSprites.clear();
		}
	}

	void BatchRenderer2D::renderText() {
		textRenderer->updateCamera();

		Renderer::enableDepthTesting(false);

		textRenderer->render(text);
		text.clear();
	}

	void BatchRenderer2D::clear() {
		transparentSprites.clear();
		sprites.clear();
		text.clear();
	}

}