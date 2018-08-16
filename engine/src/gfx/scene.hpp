//
// Created by FLXR on 8/14/2018.
//

#ifndef X808_SCENE_HPP
#define X808_SCENE_HPP


#include "world/lights/lightmanager.hpp"
#include "world/model/mesh1.hpp"

namespace xe {

	class XE_API Scene {
	public:
		explicit Scene(const std::string_view &folder, const std::string_view &name);
		~Scene();

		void addMesh(UniqueMesh *mesh) { meshes.push_back(mesh); }
		void addLight(Light *light) { lightManager->addLight(light); }

		const std::vector<UniqueMesh *> &getMeshes() const { return meshes; }
		const std::vector<Light *> &getLights() const { return lightManager->getLights(); }

	private:
		std::string folder;
		std::string name;

		LightManager *lightManager;
		std::vector<UniqueMesh *> meshes;
		std::vector<Material1 *> materials;
	};

}


#endif //X808_SCENE_HPP
