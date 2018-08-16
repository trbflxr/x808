//
// Created by FLXR on 8/16/2018.
//

#ifndef X808_SCENELOADER_HPP
#define X808_SCENELOADER_HPP


#include <vector>
#include <string>

#include "common.hpp"
#include "xeint.hpp"
#include "utils/noncopyable.hpp"
#include "world/model/uniquemesh.hpp"
#include "world/lights/light.hpp"

struct aiScene;
struct aiNode;

namespace xe {

	struct XE_API SceneLoader : NonCopyable {
		static bool load(const char *folder, const char *name,
		                 std::vector<Material1 *> &outMaterials,
		                 std::vector<UniqueMesh *> &outMeshes,
		                 std::vector<Light *> &outLights);

	private:
		static void loadMaterials(const char *folder, const aiScene *scene, std::vector<Material1 *> &materials);

		static void loadMeshes(const aiScene *scene, const aiNode *node,
		                       std::vector<UniqueMesh *> &meshes,
		                       std::vector<Material1 *> &materials);

		static void loadLights(const char *path, const aiScene *scene, std::vector<Light *> &lights);

		static api::Texture *loadTexture(const char *folder, const char *file);
	};

}


#endif //X808_SCENELOADER_HPP
