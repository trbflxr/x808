//
// Created by FLXR on 8/14/2018.
//


#include <xe/gfx/scene.hpp>
#include <xe/loaders/sceneloader.hpp>

namespace xe {

	Scene::Scene(const string &folder, const string &name) :
			folder(folder),
			name(name) {

		lightManager = new LightManager();

		SceneLoader::load(folder.data(), name.data(), materials, meshes, lightManager->getLights());
	}

	Scene::~Scene() {
		delete lightManager;

		for (auto &&material : materials) {
			delete material;
		}

		for (auto &&mesh : meshes) {
			delete mesh;
		}
	}

}
