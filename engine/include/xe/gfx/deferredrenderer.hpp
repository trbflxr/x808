//
// Created by FLXR on 3/5/2019.
//

#ifndef X808_DEFERREDRENDERER_HPP
#define X808_DEFERREDRENDERER_HPP


#include <xe/gfx/camera.hpp>
#include <xe/gfx/uniformbuffer.hpp>
#include <xe/gfx/gbuffer.hpp>
#include <xe/gfx/finalfx.hpp>
#include <xe/gfx/quad.hpp>
#include <xe/gfx/shadows.hpp>

namespace xe {

	class XE_API DeferredRenderer : NonCopyable {
	public:
		explicit DeferredRenderer(uint width, uint height, Camera *camera, ShadowParameters sp);
		~DeferredRenderer() override;

		void render(const Scene *scene) const;

		inline void useFXAA(bool enabled) { final->useFXAA(enabled); }
		inline void enableCullTest(bool enabled) { gBuffer->enableCullTest(enabled); }
		inline void enableWireframe(bool enabled) { gBuffer->enableWireframe(enabled); }
		inline void enableLightObjects(bool enabled) { gBuffer->enableLightObjects(enabled); }
		inline void enableLightBounds(bool enabled) { gBuffer->enableLightBounds(enabled); }

		inline uint getWidth() const { return width; }
		inline uint getHeight() const { return height; }

		inline const Camera *getCamera() const { return camera; }
		inline void setCamera(Camera *camera) { DeferredRenderer::camera = camera; }

		inline const vec3 &getAmbientLight() const { return ambientLight; }
		inline void setAmbientLight(const vec3 &color) { ambientLight = color; }

		inline const GBuffer *getGBuffer() const { return gBuffer; }

	private:
		void updateCamera() const;

		void renderModels(BeginMode mode, const Shader *shader, const std::vector<Model *> &models) const;
		void renderLights(BeginMode mode, const Shader *shader, const std::vector<Light *> &lights) const;
		void renderLightBounds(const Shader *shader, const Light *light) const;

		uint setTexture(const Shader *shader, const Texture *texture, const char *sampler, const char *enable) const;

	private:
		friend class GBuffer;

		uint width;
		uint height;
		Camera *camera;
		UniformBuffer *cameraUBO;

		vec3 ambientLight;

		Shadows *shadows;
		GBuffer *gBuffer;
		Quad *quad;
		FinalFX *final;
	};

}

#endif //X808_DEFERREDRENDERER_HPP
