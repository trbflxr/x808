//
// Created by FLXR on 3/6/2019.
//

#include <xe/gfx/shadows.hpp>
#include <xe/gfx/scene.hpp>

namespace xe {

	Shadows::Shadows(ShadowParameters params) :
			params(params) {

		spotShadows = new ShadowMap(params.spotSize, params.spotCount);
	}

	Shadows::~Shadows() {
		delete spotShadows;
	}

	void Shadows::render(const Scene *scene) {
		/*spotShadowsIndex = 0;

		for (const auto &light : scene->getLights()) {
			if (!light->isShadowed() || light->getShadowId() == -1) continue;

			switch (light->getType()) {
				case LightType::Spot: {
					renderSpotShadows(dynamic_cast<SpotLight *>(light), scene);
					break;
				}

				case LightType::Point: { }
				case LightType::Directional: { }

				default: break;
			}
		}*/
	}

	void Shadows::renderSpotShadows(const SpotLight *light, const Scene *scene) {
		/*if (spotShadowsIndex == params.spotCount) return;

		const int32 sid = light->getShadowId();

		spotShadows[spotShadowsIndex].first = sid;
		spotShadows[spotShadowsIndex].second->render(scene, light->getView(), light->getProjection());

		++spotShadowsIndex;*/
	}

	const Texture *Shadows::getSpotShadows(int32 id) const {
		/*for (const auto &ss : spotShadows) {
			if (ss.first == id) return ss.second->getTexture();
		}*/
		return nullptr;
	}

}
