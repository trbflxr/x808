//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_WORLDLOADER_HPP
#define X808_WORLDLOADER_HPP

#include <vector>
#include "world/model/uniquemesh.hpp"
#include "world/lights/lightmanager.hpp"

namespace xe {

	class XE_API WorldLoader {
	public:
		explicit WorldLoader(const std::string_view &path);

		bool createWorld(const std::string_view &path,
		                 std::vector<UniqueMesh *> &meshes,
		                 std::vector<Light *> lights);

		bool addWorldToScene(const std::vector<std::string_view> &paths,
		                     std::vector<UniqueMesh *> &meshes,
		                     LightManager *lightManager);

	private:
		std::array<const std::string, 2> genFilePaths(const std::string_view &file, const std::string_view &ext);

	private:
		std::string path;
	};

}

#endif //X808_WORLDLOADER_HPP
