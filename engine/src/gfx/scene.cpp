//
// Created by FLXR on 8/14/2018.
//


#include "scene.hpp"
#include "loaders/sceneloader.hpp"

namespace xe {

	Scene::Scene(const std::string_view &folder, const std::string_view &name) :
			folder(folder),
			name(name) {

		lightManager = new LightManager();

		SceneLoader::load(folder.data(), name.data(), materials, meshes, lightManager->getLights());
	}

	Scene::~Scene() {
		delete lightManager;
		materials.clear();
		meshes.clear();
	}

}
