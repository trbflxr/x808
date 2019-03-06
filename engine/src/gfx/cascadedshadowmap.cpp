//
// Created by FLXR on 3/6/2019.
//

#include <xe/gfx/cascadedshadowmap.hpp>

namespace xe {

	CascadedShadowMap::CascadedShadowMap(uint size) {
		for (uint i = 0; i < Count; ++i) {
			cascades[i] = new ShadowMap(size, 0);
		}
	}

	CascadedShadowMap::~CascadedShadowMap() {
		for (uint i = 0; i < Count; ++i) {
			delete cascades[i];
		}
	}

	void CascadedShadowMap::render(const Scene *scene, const DirectionalLight *light, const vec3 &focus) {

	}

}
