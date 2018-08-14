//
// Created by FLXR on 8/13/2018.
//

#include <sstream>
#include "worldloader.hpp"

namespace xe {

	WorldLoader::WorldLoader(const std::string_view &path) :
			path(path) {

		std::vector<UniqueMesh *> lightObjects;
	}

	bool WorldLoader::createWorld(const std::string_view &path,
	                              std::vector<UniqueMesh *> &meshes,
	                              std::vector<Light *> lights) {

		std::array<const std::string, 2> paths;

		return true;
	}

	bool WorldLoader::addWorldToScene(const std::vector<std::string_view> &paths,
	                                  std::vector<UniqueMesh *> &meshes,
	                                  LightManager *lightManager) {

		std::vector<UniqueMesh *> tempMeshes;
		std::vector<Light *> tempLights;

		for (auto &&file : paths) {
			if (!createWorld(file, tempMeshes, tempLights)) {
				//todo: err
				XE_ASSERT(false);
				return false;
			}
			meshes.insert(meshes.end(), tempMeshes.begin(), tempMeshes.end());
			lightManager->addLights(tempLights);

			tempMeshes.clear();
			tempLights.clear();
		}

		return true;
	}

	std::array<const std::string, 2> WorldLoader::genFilePaths(const std::string_view &file,
	                                                           const std::string_view &ext) {
//		std::array<const std::string, 2> r;
//		std::stringstream ss;
//
//		ss << path << "/" << file << "/" << file << ".dae";
//		r[0] = ss.str();
//
//		ss.clear();
//
//		ss << path << "/" << file << "/" << file << ".lights";
//		r[1] = ss.str();

//		return r;
	}

}