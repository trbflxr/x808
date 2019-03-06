//
// Created by FLXR on 3/6/2019.
//

#ifndef X808_CASCADEDSHADOWMAP_HPP
#define X808_CASCADEDSHADOWMAP_HPP


#include <xe/gfx/shadowmap.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	class Scene;
	class DirectionalLight;

	class XE_API CascadedShadowMap : NonCopyable {
	public:
		enum Size {
			Small,
			Medium,
			Wide,
			Count
		};

	public:
		explicit CascadedShadowMap(uint size);
		~CascadedShadowMap() override;

		void render(const Scene *scene, const DirectionalLight *light, const vec3 &focus);

		inline const Texture *getTexture(Size size) const { return cascades[size]->getTexture(); }

	private:
		std::array<ShadowMap *, Count> cascades;
	};

}


#endif //X808_CASCADEDSHADOWMAP_HPP
