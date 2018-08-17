//
// Created by FLXR on 8/14/2018.
//

#ifndef X808_SCENE_HPP
#define X808_SCENE_HPP


#include <xe/world/lights/lightmanager.hpp>
#include <xe/world/model/mesh.hpp>

namespace xe {

	class XE_API Scene {
	public:
		explicit Scene(const string &folder, const string &name);
		~Scene();

		void addMesh(UniqueMesh *mesh) { meshes.push_back(mesh); }
		void addLight(Light *light) { lightManager->addLight(light); }

		const std::vector<UniqueMesh *> &getMeshes() const { return meshes; }
		const std::vector<Light *> &getLights() const { return lightManager->getLights(); }

	private:
		string folder;
		string name;

		LightManager *lightManager;
		std::vector<UniqueMesh *> meshes;
		std::vector<Material *> materials;
	};

}


#endif //X808_SCENE_HPP
