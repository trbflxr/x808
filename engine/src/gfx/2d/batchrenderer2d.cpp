//
// Created by FLXR on 9/10/2018.
//

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

	void BatchRenderer2D::submit(const SpriteComponent *sprite, const Transform2DComponent *transform) {
		if (!sprite->visible) return;

		if (sprite->hasTransparency) {
			transparentSprites.emplace_back(sprite, transform);
		} else {
			sprites.emplace_back(sprite, transform);
		}
	}

	void BatchRenderer2D::submit(const Text *text) {
		BatchRenderer2D::text.push_back(text);
	}

	void BatchRenderer2D::renderSprites() {
		spriteRenderer->updateCamera();

		Renderer::enableDepthTesting(true);

		std::sort(sprites.begin(), sprites.end(),
		          [](const RenderTarget2D a, const RenderTarget2D b) {
			          return a.sprite->texture > b.sprite->texture;
		          });

		spriteRenderer->render(sprites);
		sprites.clear();

		//draw transparent
		if (!transparentSprites.empty()) {
			//todo: there must be a better solution
			std::sort(transparentSprites.begin(), transparentSprites.end(),
			          [](const RenderTarget2D a, const RenderTarget2D b) {
				          return a.transform->zIndex < b.transform->zIndex;
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