//
// Created by FLXR on 2/9/2019.
//

#ifndef X808_LAYER2D_HPP
#define X808_LAYER2D_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/batchrenderer2d.hpp>

namespace xe {

	class XE_API Layer2D : public Layer {
	public:
		explicit Layer2D() = default;
		~Layer2D() override;

		virtual void renderScene() { }

		void render() final;

		void createCamera(uint width, uint height, float near, float far);

		void createRenderer(uint width, uint height,
		                    bool enableLighting = false,
		                    const Shader *customShader = nullptr,
		                    const Shader *customTextShader = nullptr);

		void submit(IRenderable2D *renderable);
		void submit(Text *text);
		void submit(Light2D *light);

		void setAmbientLight(const vec3 &light);

		Camera *getCamera() { return camera; }
		const Camera *getCamera() const { return camera; }

		BatchRenderer2D *getRenderer() { return renderer; }
		const BatchRenderer2D *getRenderer() const { return renderer; }

		inline const Texture *getRenderTexture() const final { return renderer->getRenderTexture(); }

	private:
		Camera *camera;
		BatchRenderer2D *renderer;
	};

}


#endif //X808_LAYER2D_HPP
