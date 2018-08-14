//
// Created by FLXR on 8/14/2018.
//

#ifndef X808_SCENE_HPP
#define X808_SCENE_HPP


#include "world/lights/lightmanager.hpp"
#include "world/model/mesh1.hpp"

struct aiScene;
struct aiNode;

namespace xe {

	class XE_API Scene {
	public:
		explicit Scene(const std::string_view &folder, const std::string_view &name);
		~Scene();
		
	private:
		bool loadLights(const std::string_view &path);
		bool loadMeshes(const std::string_view &path);
		api::Texture *loadTexture(const char *file);

		void recursiveLoad(const aiScene* scene, const aiNode* node);

	private:
		//todo: remove
	public:
		std::string folder;

		LightManager *lightManager;
		std::vector<UniqueMesh *> meshes;
		std::vector<Material1 *> materials;
	};

}


#endif //X808_SCENE_HPP
