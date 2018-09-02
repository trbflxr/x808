//
// Created by FLXR on 8/18/2018.
//

#ifndef X808_GBUFFER_HPP
#define X808_GBUFFER_HPP


#include <xe/common.hpp>
#include <xe/gfx/fx/quad.hpp>
#include <xe/gfx/fx/rendereffect.hpp>
#include <xe/gfx/texture.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/gfx/scene.hpp>
#include <xe/gfx/lights/spotlight.hpp>
#include <xe/gfx/lights/pointlight.hpp>

namespace xe { namespace fx {

	class XE_API GBuffer : public RenderEffect {
	public:
		explicit GBuffer(uint width, uint height);
		~GBuffer() override;

		inline void enableWireframe(bool enabled) const { drawWireframe = enabled; }
		inline void enableLightObjects(bool enabled) const { drawLightObjects = enabled; }
		inline void enableLightBounds(bool enabled) const { drawLightBounds = enabled; }

		void passDeferredShading(const Scene *scene) const;

		void passLightAccumulation(Quad *quad, const FrameBuffer *finalScene) const;

		inline const Texture *getDepthStencilTexture() const { return depthStencilTexture; }
		inline const Texture *getDiffuseTexture() const { return diffuseTexture; }
		inline const Texture *getNormalDepthTexture() const { return normalDepthTexture; }
		inline const Texture *getSpecularTexture() const { return specularTexture; }
		inline const Texture *getLightDiffuseTexture() const { return lightDiffuseTexture; }
		inline const Texture *getLightSpecularTexture() const { return lightSpecularTexture; }

	private:
		void createTextures();
		void createShaders();

		void passGeometry(const Scene *scene) const;
		void passStencil(const Light *light) const;
		void passSpotLight(const SpotLight *light) const;
		void passPointLight(const PointLight *light) const;

	private:
		mutable bool drawWireframe;
		mutable bool drawLightObjects;
		mutable bool drawLightBounds;

		FrameBuffer *gBuffer;

		Shader *geometryShader;
		Shader *stencilShader;
		Shader *spotShader;
		Shader *pointShader;
		Shader *accumulationShader;

		Texture *depthStencilTexture;
		Texture *diffuseTexture;
		Texture *normalDepthTexture;
		Texture *specularTexture;
		Texture *lightDiffuseTexture;
		Texture *lightSpecularTexture;
	};


}}


#endif //X808_GBUFFER_HPP
