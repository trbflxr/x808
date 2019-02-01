//
// Created by FLXR on 8/14/2018.
//


#include <xe/gfx/scene.hpp>
#include <xe/loaders/sceneloader.hpp>
#include <xe/gfx/scenerenderer.hpp>
#include <xe/gfx/defaultuniforms.hpp>

namespace xe {

	Scene::Scene(const string &folder, const string &name) :
			folder(folder),
			name(name) {

		lightManager = new LightManager();

		SceneLoader::load(folder.c_str(), name.c_str(), materials, meshes, lightManager->getLights());
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

	void Scene::update(const Transform &cameraTransform, float delta) {
		lightManager->update(-cameraTransform.getPosition(), delta);
	}

	void Scene::render(BeginMode mode, const Shader *shader, bool drawLightObjects, bool drawLightBounds) const {
		static constexpr int32 enabled = 1;
		static constexpr int32 disabled = 0;

		shader->setUniform(uniform::cullTest, &enabled, sizeof(int32));
		renderMeshes(mode, shader);

		//draw light objects
		if (drawLightObjects) {
			shader->setUniform(uniform::cullTest, &disabled, sizeof(int32));
			renderLightObjects(mode, shader, drawLightBounds);
		}
	}

	void Scene::renderMeshes(BeginMode mode, const Shader *shader) const {
		SceneRenderer::drawMeshes(mode, meshes, shader, mat4::identity(), 0.0f, true);
	}

	void Scene::renderMeshesBasic(BeginMode mode, const Shader *shader) const {
		SceneRenderer::drawMeshes(mode, meshes, shader, mat4::identity(), 0.0f, false);
	}

	void Scene::renderLightObjects(BeginMode mode, const Shader *shader, bool drawLightBounds) const {
		SceneRenderer::drawLights(mode, lightManager->getLights(), shader, mat4::identity(), 0.0f, drawLightBounds);
	}

}
