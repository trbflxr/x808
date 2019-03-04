//
// Created by FLXR on 3/2/2019.
//

#ifndef X808_GBUFFER_HPP
#define X808_GBUFFER_HPP


#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/model.hpp>
#include <xe/gfx/light.hpp>
#include <xe/gfx/quad.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	class XE_API GBuffer : NonCopyable {
	public:
		explicit GBuffer(uint width, uint height);
		~GBuffer() override;

		void passGeometry(const std::vector<Model *> &models, const std::vector<Light *> &lights) const;
		void passLightAccumulation(const Quad *quad, const FrameBuffer *final) const;

		inline void enableCullTest(bool enabled) const { cullTest = enabled; }
		inline void enableWireframe(bool enabled) const { drawWireframe = enabled; }
		inline void enableLightObjects(bool enabled) const { drawLightObjects = enabled; }
		inline void enableLightBounds(bool enabled) const { drawLightBounds = enabled; }

		inline uint getWidth() const { return width; }
		inline uint getHeight() const { return height; }

		inline const Texture *getDepthStencilTexture() const { return depthStencilTexture; }
		inline const Texture *getDiffuseTexture() const { return diffuseTexture; }
		inline const Texture *getNormalTexture() const { return normalTexture; }
		inline const Texture *getSpecularTexture() const { return specularTexture; }
		inline const Texture *getPositionTexture() const { return positionTexture; }
		inline const Texture *getLightDiffuseTexture() const { return lightDiffuseTexture; }
		inline const Texture *getLightSpecularTexture() const { return lightSpecularTexture; }

	private:
		void createTextures();
		void createShaders();

		void renderModels(BeginMode mode, const Shader *shader, const std::vector<Model *> &models) const;
		void renderLights(BeginMode mode, const Shader *shader, const std::vector<Light *> &lights) const;
		void renderLightBounds(const Shader *shader, const Light *light) const;

		void passGeometryInternal(const std::vector<Model *> &models, const std::vector<Light *> &lights) const;
		void passStencil(const Light *light) const;
		void passSpotLight(const SpotLight *light) const;
		void passPointLight(const PointLight *light) const;

		int32 setTexture(const Shader *shader, const Texture *t, const char *sampler, const char *enable) const;

	private:
		uint width;
		uint height;
		vec2 renderSize;

		mutable bool cullTest;
		mutable bool drawWireframe;
		mutable bool drawLightObjects;
		mutable bool drawLightBounds;

		FrameBuffer *gBuffer;

		const Shader *geometryShader;
		const Shader *stencilShader;
		const Shader *accumulationShader;
		const Shader *spotShader;
		const Shader *pointShader;

		const Texture *depthStencilTexture;
		const Texture *diffuseTexture;
		const Texture *normalTexture;
		const Texture *specularTexture;
		const Texture *positionTexture;
		const Texture *lightDiffuseTexture;
		const Texture *lightSpecularTexture;
	};

}

#endif //X808_GBUFFER_HPP
