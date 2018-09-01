//
// Created by FLXR on 8/13/2018.
//

#include <xe/gfx/uniformbuffer.hpp>
#include <xe/world/lights/lightmanager.hpp>

namespace xe {

	LightManager::LightManager() :
			lightCount(0) {}

	LightManager::~LightManager() {
		for (auto &&light : lights) {
			delete light;
		}
	}

	void LightManager::addLight(Light *light) {
		light->id = lightCount;
		light->enabled = true;

		lights.push_back(light);
		++lightCount;
	}

	void LightManager::addLights(std::vector<Light *> lights) {
		for (auto &&light : lights) {
			addLight(light);
		}
	}

}
