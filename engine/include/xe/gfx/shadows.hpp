//
// Created by FLXR on 3/6/2019.
//

#ifndef X808_SHADOWS_HPP
#define X808_SHADOWS_HPP


#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/uniformbuffer.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	class Camera;
	class Scene;
	class SpotLight;
	class PointLight;
	class DirectionLight;

	struct ShadowParameters {
		uint spotSize;
		uint maxSpotCount;

		explicit ShadowParameters(uint spotSize = 512,
		                          uint maxSpotCount = 4) :
				spotSize(spotSize),
				maxSpotCount(maxSpotCount) { }
	};

	class XE_API Shadows : NonCopyable {
	public:
		explicit Shadows(ShadowParameters params);
		~Shadows() override;

		void render(const Scene *scene);

		inline const Texture *getSpotShadows() const { return spotTexture; }

	private:
		void renderSpotShadows(const Scene *scene);

	private:
		ShadowParameters params;

		int32 spotShadowsIndex;
		FrameBuffer *spotBuffer;
		UniformBuffer *spotUBO;
		const Texture *spotDepthTexture;
		const Texture *spotTexture;
		const Shader *spotShader;
	};

}


#endif //X808_SHADOWS_HPP
