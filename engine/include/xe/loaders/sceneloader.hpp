//
// Created by FLXR on 8/16/2018.
//

#ifndef X808_SCENELOADER_HPP
#define X808_SCENELOADER_HPP


#include <vector>
#include <string>

#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/utils/noncopyable.hpp>
#include <xe/gfx/uniquemesh.hpp>
#include <xe/gfx/lights/light.hpp>

struct aiScene;
struct aiNode;

namespace xe {

	struct XE_API SceneLoader : NonCopyable {
		static bool load(const string &folder, const string &name,
		                 std::vector<Material *> &outMaterials,
		                 std::vector<UniqueMesh *> &outMeshes,
		                 std::vector<Light *> &outLights);

	private:
		static void loadMaterials(const string &folder, const aiScene *scene, std::vector<Material *> &materials);

		static void loadMeshes(const aiScene *scene, const aiNode *node,
		                       std::vector<UniqueMesh *> &meshes,
		                       std::vector<Material *> &materials);

		static void loadLights(const string &path, const aiScene *scene, std::vector<Light *> &lights);

		static const Texture *loadTexture(const string &folder, const string &file);
	};

}


#endif //X808_SCENELOADER_HPP
