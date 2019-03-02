//
// Created by FLXR on 3/2/2019.
//

#include <xe/loaders/modelloader.hpp>
#include <xe/core/vfs.hpp>
#include <xe/core/filesystem.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace xe {

	ModelLoader::ModelLoader() {
		importer = new Assimp::Importer;
	}

	ModelLoader::~ModelLoader() {
		delete importer;
	}

	ModelLoader &ModelLoader::get() {
		static ModelLoader ml;
		return ml;
	}

	IndexedModel *ModelLoader::loadIndexedModel(const string &file) {
		const aiScene *scene = loadScene(get().importer, file);
		if (!scene) {
			return nullptr;
		}

		aiNode *node = scene->mRootNode;

		if (node->mNumChildren == 0) {
			XE_CORE_ERROR("[ModelLoader]: no meshes in scene '", file, "'");
			return nullptr;
		}

		const aiMesh *m = scene->mMeshes[node->mChildren[0]->mMeshes[0]];

		return new IndexedModel(m);
	}

	bool ModelLoader::loadModel(Model *model, const string &file) {
		const aiScene *scene = loadScene(get().importer, file);
		if (!scene) {
			return false;
		}

		aiNode *node = scene->mRootNode;

		if (node->mNumChildren == 0) {
			XE_CORE_ERROR("[ModelLoader]: no meshes in scene '", file, "'");
			return false;
		}

		const aiMesh *m = scene->mMeshes[node->mChildren[0]->mMeshes[0]];

		const IndexedModel indexedModel(m);

		mat4 t;
		const aiMatrix4x4 ait = scene->mRootNode->mTransformation * node->mTransformation;
		memcpy(&t, &ait, sizeof(mat4));

		model->set(t);
		model->init(indexedModel);

		return true;
	}

	const aiScene *ModelLoader::loadScene(Assimp::Importer *importer, const string &file) {
		string path(file);

		if (!FileSystem::exists(path)) {
			path.insert(0, basePath);
		}

		int64 memorySize;
		byte *memory = VFS::readFile(path, &memorySize);

		if (!memory) {
			XE_CORE_ERROR("[ModelLoader]: unable to read file: '", path, "'");
			return nullptr;
		}

		const aiScene *scene = importer->ReadFileFromMemory(memory, static_cast<size_t>(memorySize),
		                                                    aiProcessPreset_TargetRealtime_MaxQuality |
		                                                    aiProcess_JoinIdenticalVertices |
		                                                    aiProcess_Triangulate |
		                                                    aiProcess_GenSmoothNormals |
		                                                    aiProcess_CalcTangentSpace |
		                                                    aiProcess_FlipUVs);

		delete[] memory;

		if (!scene) {
			XE_CORE_ERROR("[ModelLoader]: unable to load scene: '", path, "'");
			return nullptr;
		}

		return scene;
	}

}