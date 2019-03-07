//
// Created by FLXR on 3/6/2019.
//

#ifndef X808_SHADOWS_HPP
#define X808_SHADOWS_HPP


#include <xe/gfx/shadowmap.hpp>
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

		const Texture *getSpotShadows(int32 id) const;

	private:
		void renderSpotShadows(const SpotLight *light, const Scene *scene);
//		void renderDirectionalShadows(const DirectionLight *light, const Scene *scene);

	private:
		ShadowParameters params;

		uint spotShadowsIndex;
		std::vector<std::pair<int32, ShadowMap *>> spotShadows;
	};

}


#endif //X808_SHADOWS_HPP
