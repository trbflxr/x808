//
// Created by FLXR on 3/6/2019.
//

#include <xe/gfx/scene.hpp>

namespace xe {

	Scene::Scene() {

	}

	Scene::~Scene() {
		for (const auto &m : models) {
			delete m;
		}

		for (const auto &l : lights) {
			delete l;
		}
	}

	void Scene::add(Model *model) {
		models.push_back(model);
	}

	void Scene::add(Light *light) {
		lights.push_back(light);

		switch (light->getType()) {
			case LightType::Spot: {
				spotLights.push_back(dynamic_cast<SpotLight *>(light));
				break;
			}

			case LightType::Point: {
				pointLights.push_back(dynamic_cast<PointLight *>(light));
				break;
			}

			case LightType::Directional: {
				directionalLights.push_back(dynamic_cast<DirectionalLight *>(light));
				break;
			}

			default: break;
		}
	}

	void Scene::updateLights(const Camera *camera) {
		//todo: sort lights and frustum culling
	}

}
