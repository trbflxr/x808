//
// Created by FLXR on 8/14/2018.
//

#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "scene.hpp"
#include "utils/string.hpp"
#include "resources/texturemanager.hpp"

namespace xe {

	Scene::Scene(const std::string_view &folder, const std::string_view &name) :
			folder(folder) {

		std::string r[2];
		std::stringstream ss;

		ss << folder << "/" << name << ".dae";
		r[0] = ss.str();

		ss.str("");

		ss << folder << "/" << name << ".lights";
		r[1] = ss.str();

		loadMeshes(r[0]);
	}

	Scene::~Scene() {
		materials.clear();
	}

	bool Scene::loadLights(const std::string_view &path) {
		XE_INFO(path);

		return true;
	}

	bool Scene::loadMeshes(const std::string_view &path) {
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path.data(),
		                                         aiProcessPreset_TargetRealtime_MaxQuality |
		                                         aiProcess_JoinIdenticalVertices |
		                                         aiProcess_Triangulate |
		                                         aiProcess_GenSmoothNormals |
		                                         aiProcess_CalcTangentSpace |
		                                         aiProcess_FlipUVs);
		if (!scene) {
			XE_FATAL("[Mesh]: unable to load model '", path, "'");
			XE_ASSERT(false);
			return false;
		}


		for (int i = 0; i < scene->mNumMaterials; ++i) {
			aiMaterial *material = scene->mMaterials[i];

			//load material data
			aiString temp;
			aiColor4D diffuse;
			aiColor4D emission;
			aiColor4D specular;
			float shininess;

			material->Get(AI_MATKEY_NAME, temp);
			material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
			material->Get(AI_MATKEY_COLOR_EMISSIVE, emission);
			material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
			material->Get(AI_MATKEY_SHININESS, shininess);

			Material1 *m = new Material1(temp.C_Str());
			m->diffuseColor = vec3(diffuse.r, diffuse.g, diffuse.b);
			m->specularColor = vec3(specular.r, specular.g, specular.b);
			m->emission = emission.a * 5.0f;
			m->specularShininess = shininess;

			//load textures
			aiReturn texFound;

			texFound = material->GetTexture(aiTextureType_DIFFUSE, 0, &temp);
			if (texFound == AI_SUCCESS) {
				m->diffuse = loadTexture(temp.C_Str());
			}

			texFound = material->GetTexture(aiTextureType_SPECULAR, 0, &temp);
			if (texFound == AI_SUCCESS) {
				m->specular = loadTexture(temp.C_Str());
			}

			texFound = material->GetTexture(aiTextureType_NORMALS, 0, &temp);
			if (texFound == AI_SUCCESS) {
				m->normal = loadTexture(temp.C_Str());
			}

			texFound = material->GetTexture(aiTextureType_DISPLACEMENT, 0, &temp);
			if (texFound == AI_SUCCESS) {
				m->displacement = loadTexture(temp.C_Str());
			}

			texFound = material->GetTexture(aiTextureType_REFLECTION, 0, &temp);
			if (texFound == AI_SUCCESS) {
				m->parallax = loadTexture(temp.C_Str());
			}

			materials.push_back(m);
		}

		recursiveLoad(scene, scene->mRootNode);

		return true;
	}

	void Scene::recursiveLoad(const aiScene *scene, const aiNode *node) {
		for (uint i = 0; i < node->mNumMeshes; ++i) {
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			Material1 *material = materials[mesh->mMaterialIndex];

			IndexedModel indexedModel(mesh);
			std::string id = mesh->mName.C_Str();

			aiMatrix4x4 transformation = scene->mRootNode->mTransformation * node->mTransformation;
			mat4 t(1.0f);
			memcpy(&t, &transformation, sizeof(mat4));

			UniqueMesh *uniqueMesh = new UniqueMesh(id, new Mesh1(id, indexedModel, material), t);

			meshes.push_back(uniqueMesh);
		}

		for (uint n = 0; n < node->mNumChildren; ++n) {
			recursiveLoad(scene, node->mChildren[n]);
		}
	}

	api::Texture *Scene::loadTexture(const char *file) {
		static api::TextureParameters params(TextureTarget::Tex2D,
		                                     PixelInternalFormat::Rgba,
		                                     PixelFormat::Rgba,
		                                     PixelType::UnsignedByte,
		                                     TextureMinFilter::LinearMipMapLinear,
		                                     TextureMagFilter::Linear,
		                                     TextureWrap::Repeat,
		                                     MIP_MAP_AUTO,
		                                     ANISOTROPY_AUTO);

		std::string texturePath = folder + "/" + file;
		std::string textureName = utils::getFileName(file, false);

		api::Texture *texture = api::Texture::create(textureName, texturePath, params);
		TextureManager::add(texture, false);

		return texture;
	}
}
