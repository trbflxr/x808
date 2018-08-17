//
// Created by FLXR on 8/14/2018.
//


#include <xe/gfx/scene.hpp>
#include <xe/loaders/sceneloader.hpp>
#include <xe/gfx/scenerenderer.hpp>

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

	void Scene::update(const SpatialData &cameraSpatial, float delta) {
		lightManager->update(-cameraSpatial.position, delta);
	}

	void Scene::render(BeginMode mode, Shader *shader) {
		renderMeshes(mode, shader);
		renderLightObjects(mode, shader);
	}

	void Scene::renderMeshes(BeginMode mode, Shader *shader) {
		SceneRenderer::drawMeshes(mode, meshes, shader, mat4(1.0f), 0.0f, 10);
	}

	void Scene::renderMeshesWithMaterials(BeginMode mode, Shader *shader) {
		SceneRenderer::drawMeshes(mode, meshes, shader, mat4(1.0f), 0.0f, 1);
	}

	void Scene::renderMeshesBasic(BeginMode mode, Shader *shader) {
		SceneRenderer::drawMeshes(mode, meshes, shader, mat4(1.0f), 0.0f, 0);
	}

	void Scene::renderLightObjects(BeginMode mode, Shader *shader) {
		SceneRenderer::drawLights(mode, lightManager->getLights(), shader, mat4(1.0f), 0.0f, false);
	}

}
