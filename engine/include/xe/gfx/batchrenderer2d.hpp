//
// Created by FLXR on 9/10/2018.
//

#ifndef X808_BATCHRENDERER2D_HPP
#define X808_BATCHRENDERER2D_HPP


#include <xe/gfx/shader.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/uniformbuffer.hpp>
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/textrenderer.hpp>
#include <xe/gfx/2d/light2d.hpp>

namespace xe {

	class XE_API BatchRenderer2D {
	public:
		explicit BatchRenderer2D(uint width, uint height, Camera *camera,
		                         bool enableLighting = false,
		                         const Shader *customShader = nullptr,
		                         const Shader *customTextShader = nullptr);
		~BatchRenderer2D();

		void submit(const IRenderable2D *target);
		void submit(const Text *text);
		void submit(const Light2D *light);

		void setAmbientLight(const vec3 &color);

		void render();

		void clear();

		inline Renderer2D *getRenderer2D() const { return renderer; }
		inline void enableWireframe(bool flag) { renderer->enableWireframe(flag); }

		inline const Texture *getRenderTexture() const { return renderTexture; }

	private:
		void renderSpritesInternal();

	private:
		Camera *camera;

		Renderer2D *renderer;
		TextRenderer *textRenderer;

		FrameBuffer *buffer;
		Texture *renderTexture;

		bool enableLighting;
		vec3 ambient;
		UniformBuffer *lightUBO;

		std::vector<const Light2D *> lights;
		std::vector<const IRenderable2D *> targets;
		std::vector<const IRenderable2D *> transparentTargets;
		std::vector<const Text *> text;
	};

}


#endif //X808_BATCHRENDERER2D_HPP
