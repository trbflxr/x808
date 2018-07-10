//
// Created by FLXR on 7/10/2018.
//

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "loadmodel.hpp"
#include "utils/log.hpp"

namespace xe { namespace utils {

	bool loadModels(const std::string_view &path, std::vector<gfx::IndexedModel> &models) {

		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path.data(),
		                                         aiProcess_Triangulate |
		                                         aiProcess_GenSmoothNormals |
		                                         aiProcess_FlipUVs |
		                                         aiProcess_CalcTangentSpace);

		if (!scene) {
			XE_FATAL("Mesh load failed: ", path.data());
			XE_ASSERT(false);
			return false;
		}

		for (uint32 j = 0; j < scene->mNumMeshes; j++) {
			const aiMesh *model = scene->mMeshes[j];

			gfx::IndexedModel newModel(model);

			models.push_back(newModel);
		}

		return true;
	}

}}