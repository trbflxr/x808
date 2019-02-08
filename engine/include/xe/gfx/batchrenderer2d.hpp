//
// Created by FLXR on 9/10/2018.
//

#ifndef X808_BATCHRENDERER2D_HPP
#define X808_BATCHRENDERER2D_HPP


#include <xe/gfx/shader.hpp>
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/textrenderer.hpp>

namespace xe {

	class XE_API BatchRenderer2D {
	public:
		explicit BatchRenderer2D(uint width, uint height, Camera *camera,
		                         Shader *customShader = nullptr,
		                         Shader *customTextShader = nullptr);
		~BatchRenderer2D();

		void submit(const IRenderable2D *target);
		void submit(const Text *text);

		void renderSprites();
		void renderText();

		void clear();

		inline Renderer2D *getRenderer2D() const { return renderer; }
		inline void enableWireframe(bool flag) { renderer->enableWireframe(flag); }

	private:
		Camera *camera;

		Renderer2D *renderer;
		TextRenderer *textRenderer;

		std::vector<const IRenderable2D *> targets;
		std::vector<const IRenderable2D *> transparentTargets;

		std::vector<const Text *> text;
	};

}


#endif //X808_BATCHRENDERER2D_HPP
