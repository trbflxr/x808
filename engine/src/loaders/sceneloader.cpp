//
// Created by FLXR on 8/16/2018.
//


#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <xe/utils/string.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/loaders/sceneloader.hpp>
#include <xe/gfx/lights/spotlight.hpp>
#include <xe/gfx/lights/pointlight.hpp>

namespace xe {

	bool SceneLoader::load(const wchar_t *folder, const wchar_t *name,
	                       std::vector<Material *> &outMaterials,
	                       std::vector<UniqueMesh *> &outMeshes,
	                       std::vector<Light *> &outLights) {

		wchar_t paths[2][1024];

		//collada path
		wcscpy(paths[0], folder);
		wcscat(paths[0], L"/");
		wcscat(paths[0], name);
		wcscat(paths[0], L".dae");

		//lights path
		wcscpy(paths[1], folder);
		wcscat(paths[1], L"/");
		wcscat(paths[1], name);
		wcscat(paths[1], L".lights");


		//read file to memory
		FILE *file = _wfopen(paths[0], L"rb");

		if (!file) {
			fclose(file);
			XE_FATAL(L"[SceneLoader]: unable to read file '", paths[0], L"'");
			XE_ASSERT(false);
			return false;
		}

		fseek(file, 0, SEEK_END);
		const size_t size = (size_t) ftell(file);
		rewind(file);

		byte *buff = new byte[size + 1];
		buff[size] = 0;
		fread(buff, size, 1, file);

		fclose(file);

		//load assimp scene
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFileFromMemory(buff, size,
		                                                   aiProcessPreset_TargetRealtime_MaxQuality |
		                                                   aiProcess_JoinIdenticalVertices |
		                                                   aiProcess_Triangulate |
		                                                   aiProcess_GenSmoothNormals |
		                                                   aiProcess_CalcTangentSpace |
		                                                   aiProcess_FlipUVs);
		delete[] buff;

		if (!scene) {
			XE_FATAL(L"[SceneLoader]: unable to load scene '", paths[0], L"'");
			XE_ASSERT(false);
			return false;
		}

		//load xe scene
		loadMaterials(folder, scene, outMaterials);
		loadMeshes(scene, scene->mRootNode, outMeshes, outMaterials);
		loadLights(paths[1], scene, outLights);

		return true;
	}

	void SceneLoader::loadMaterials(const wchar_t *folder, const aiScene *scene, std::vector<Material *> &materials) {
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

			Material *m = new Material(temp.C_Str());
			m->diffuseColor = vec3(diffuse.r, diffuse.g, diffuse.b);
			m->specularColor = vec3(specular.r, specular.g, specular.b);
			m->emission = emission.a;
			m->specularShininess = shininess;

			//load textures
			aiReturn texFound;

			texFound = material->GetTexture(aiTextureType_DIFFUSE, 0, &temp);
			if (texFound == AI_SUCCESS) {
				m->diffuse = loadTexture(folder, temp.C_Str());
			}

			texFound = material->GetTexture(aiTextureType_SPECULAR, 0, &temp);
			if (texFound == AI_SUCCESS) {
				m->specular = loadTexture(folder, temp.C_Str());
			}

			texFound = material->GetTexture(aiTextureType_NORMALS, 0, &temp);
			if (texFound == AI_SUCCESS) {
				m->normal = loadTexture(folder, temp.C_Str());
			}

			texFound = material->GetTexture(aiTextureType_DISPLACEMENT, 0, &temp);
			if (texFound == AI_SUCCESS) {
				m->displacement = loadTexture(folder, temp.C_Str());
			}

			texFound = material->GetTexture(aiTextureType_REFLECTION, 0, &temp);
			if (texFound == AI_SUCCESS) {
				m->parallax = loadTexture(folder, temp.C_Str());
			}

			materials.push_back(m);
		}
	}

	void SceneLoader::loadMeshes(const aiScene *scene, const aiNode *node,
	                             std::vector<UniqueMesh *> &meshes,
	                             std::vector<Material *> &materials) {

		for (uint i = 0; i < node->mNumMeshes; ++i) {
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			Material *material = materials[mesh->mMaterialIndex];

			IndexedModel indexedModel(mesh);
			const char *id = mesh->mName.C_Str();

			mat4 t;
			aiMatrix4x4 ait = scene->mRootNode->mTransformation * node->mTransformation;
			memcpy(&t, &ait, sizeof(mat4));

			meshes.push_back(new UniqueMesh(id, new Mesh(id, indexedModel, material), t));
		}

		for (uint n = 0; n < node->mNumChildren; ++n) {
			loadMeshes(scene, node->mChildren[n], meshes, materials);
		}
	}

	void SceneLoader::loadLights(const wchar_t *path, const aiScene *scene, std::vector<Light *> &lights) {
		//info
		std::vector<string> ids;
		std::vector<string> types;
		std::vector<float> intensities;
		std::vector<vec3> colors;
		std::vector<float> falloffs;
		std::vector<float> spotAngles;
		std::vector<float> spotBlurs;
		std::vector<bool> shadows;

		//read light file
		std::ifstream file(path);
		if (!file.good()) {
			file.close();
			XE_WARN(L"[SceneLoader]: .lights file '", path, "' not found");
			return;
		}

		string line;
		while (std::getline(file, line)) {
			if (line.empty()) continue;

			string key = line.substr(0, 4);
			std::vector<string> values = utils::splitString(line.substr(4), ' ');

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

			}
		}

		file.close();

		//load lights
		for (uint i = 0; i < scene->mNumLights; ++i) {
			const aiNode *lightNode = scene->mRootNode->FindNode(scene->mLights[i]->mName);
			if (!lightNode) continue;

			const char *lightName = scene->mLights[i]->mName.C_Str();

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
				static const mat4 yup = mat4::rotation(90.0f, vec3::UnitZ);
				t *= yup;

				lights.push_back(new SpotLight(ids[id], colors[id], intensities[id], falloffs[id],
				                               spotAngles[id], spotBlurs[id], shadows[id], Mesh::spotLightMesh(), t));

			} else if (types[id] == "POINT") {
				lights.push_back(new PointLight(ids[id], colors[id], intensities[id], falloffs[id],
				                                shadows[id], Mesh::pointLightMesh(), t));
			}
		}
	}

	const Texture *SceneLoader::loadTexture(const wchar_t *folder, const char *file) {
		static TextureParameters params(TextureTarget::Tex2D,
		                                PixelInternalFormat::Rgba,
		                                PixelFormat::Rgba,
		                                PixelType::UnsignedByte,
		                                TextureMinFilter::LinearMipMapLinear,
		                                TextureMagFilter::Linear,
		                                TextureWrap::Repeat,
		                                MIP_MAP_AUTO,
		                                ANISOTROPY_AUTO);

		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

		wchar_t path[1024];
		wcscpy(path, folder);
		wcscat(path, L"/");
		wcscat(path, converter.from_bytes(file).c_str());

		string textureName = utils::getFileName(file, false);

		Texture *texture = new Texture(textureName, path, params);
		if (!TextureManager::add(texture)) {
			return GETTEXTURE(textureName);
		}

		return texture;
	}

}