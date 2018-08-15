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

#include <cstdio>
#include <fstream>

namespace xe {

	Scene::Scene(const std::string_view &folder, const std::string_view &name) :
			folder(folder) {

		lightManager = new LightManager();

		//create paths
		std::array<std::string, 2> paths;

		std::stringstream ss;

		ss << folder << "/" << name << ".dae";
		paths[0] = ss.str();

		ss.str("");

		ss << folder << "/" << name << ".lights";
		paths[1] = ss.str();

		load(paths);
	}

	Scene::~Scene() {
		delete lightManager;
		materials.clear();
		meshes.clear();
	}

	bool Scene::load(const std::array<std::string, 2> &paths) {
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(paths[0].c_str(),
		                                         aiProcessPreset_TargetRealtime_MaxQuality |
		                                         aiProcess_JoinIdenticalVertices |
		                                         aiProcess_Triangulate |
		                                         aiProcess_GenSmoothNormals |
		                                         aiProcess_CalcTangentSpace |
		                                         aiProcess_FlipUVs);
		if (!scene) {
			XE_FATAL("[Scene]: unable to load scene '", paths[0], "'");
			XE_ASSERT(false);
			return false;
		}

		for (uint i = 0; i < scene->mNumMaterials; ++i) {
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

		//load meshes
		recursiveLoad(scene, scene->mRootNode);

		//load lights
		loadLights(paths[1], scene);

		return true;
	}

	bool Scene::loadLights(const std::string &path, const aiScene *scene) {
		//info
		uint size = 0;
		std::vector<std::string> ids;
		std::vector<std::string> types;
		std::vector<float> intensities;
		std::vector<vec3> colors;
		std::vector<float> falloffs;
		std::vector<float> spotAngles;
		std::vector<float> spotBlurs;
		std::vector<bool> shadows;

		//read light file
		std::ifstream file(path);
		std::string line;
		while (std::getline(file, line)) {
			if (line.empty()) continue;

			std::string key = line.substr(0, 4);
			std::vector<std::string> values = utils::splitString(line.substr(4), ' ');

			if (key == "nam ") {
				std::replace(values[0].begin(), values[0].end(), '.', '_');
				ids.push_back(values[0]);

			} else if (key == "typ ") {
				types.push_back(values[0]);

			} else if (key == "ity ") {
				intensities.push_back(std::stof(values[0]));

			} else if (key == "col ") {
				colors.emplace_back(std::stof(values[0]), std::stof(values[1]), std::stof(values[2]));

			} else if (key == "fal ") {
				falloffs.emplace_back(std::stof(values[0]));

			} else if (key == "ang ") {
				spotAngles.emplace_back(std::stof(values[0]));

			} else if (key == "blr ") {
				spotBlurs.emplace_back(std::stof(values[0]));

			} else if (key == "sha ") {
				shadows.push_back(static_cast<bool>(std::stoi(values[0])));

			} else if (key == "num ") {
				size = std::stoul(values[0]);
			}
		}

		file.close();

		//load lights
		for (uint i = 0; i < scene->mNumLights; ++i) {
			const aiNode *lightNode = scene->mRootNode->FindNode(scene->mLights[i]->mName);
			if (!lightNode) continue;

			std::string lightName = scene->mLights[i]->mName.C_Str();

			mat4 t;
			aiMatrix4x4 ait = scene->mRootNode->mTransformation * lightNode->mTransformation;
			memcpy(&t, &ait, sizeof(mat4));

			uint id = 0;
			for (uint j = 0; j < ids.size(); ++j) {
				if (ids[j] == lightName) {
					id = j;
					break;
				}
			}

			if (types[id] == "SPOT") {
				t *= mat4::rotation(quat(vec3::ZAXIS, -90.0f) * quat(vec3::XAXIS, 90.0f));

				lightManager->addLight(new SpotLight1(ids[id], colors[id], intensities[id], falloffs[id],
				                                      spotAngles[id], spotBlurs[id], shadows[id],
				                                      Mesh1::spotLightMesh(), t));

			} else if (types[id] == "POINT") {
				lightManager->addLight(new PointLight1(ids[id], colors[id], intensities[id], falloffs[id],
				                                       shadows[id], Mesh1::pointLightMesh(), t));
			}
		}

		return true;
	}

	void Scene::recursiveLoad(const aiScene *scene, const aiNode *node) {
		for (uint i = 0; i < node->mNumMeshes; ++i) {
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			Material1 *material = materials[mesh->mMaterialIndex];

			IndexedModel indexedModel(mesh);
			std::string id = mesh->mName.C_Str();

			mat4 t;
			aiMatrix4x4 ait = scene->mRootNode->mTransformation * node->mTransformation;
			memcpy(&t, &ait, sizeof(mat4));

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
