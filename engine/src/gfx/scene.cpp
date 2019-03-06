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
	}

}
