//
// Created by FLXR on 7/10/2018.
//

#include <assimp/mesh.h>
#include "indexedmodel.hpp"
#include "math/geometry.hpp"

namespace xe {

	IndexedModel::IndexedModel(const aiMesh *mesh) {

		if (mesh->HasPositions()) {
			for (uint i = 0; i < mesh->mNumVertices; ++i) {
				positions.emplace_back(mesh->mVertices[i].x,
				                       mesh->mVertices[i].y,
				                       mesh->mVertices[i].z);
			}
		}

		if (mesh->HasTextureCoords(0)) {
			for (uint i = 0; i < mesh->mNumVertices; ++i) {
				uvs.emplace_back(mesh->mTextureCoords[0][i].x,
				                 mesh->mTextureCoords[0][i].y);
			}
		}

		if (mesh->HasNormals()) {
			for (uint i = 0; i < mesh->mNumVertices; ++i) {
				normals.emplace_back(mesh->mNormals[i].x,
				                     mesh->mNormals[i].y,
				                     mesh->mNormals[i].z);
			}
		}

		if (mesh->HasTangentsAndBitangents()) {
			for (uint i = 0; i < mesh->mNumVertices; ++i) {
				tangents.emplace_back(mesh->mTangents[i].x,
				                      mesh->mTangents[i].y,
				                      mesh->mTangents[i].z);
			}
		}

		if (mesh->HasFaces()) {
			for (uint i = 0; i < mesh->mNumFaces; ++i) {
				for (uint j = 0; j < mesh->mFaces[i].mNumIndices; ++j) {
					indices.push_back(mesh->mFaces[i].mIndices[j]);
				}
			}
		}
	}

	IndexedModel IndexedModel::getConeModel() {
		IndexedModel model;

		auto im = geometry::makeCone(2.0f, 4.0f, 15);

		model.positions = im.first;
		model.indices = im.second;

		model.uvs.reserve(model.positions.size());
		model.normals.reserve(model.positions.size());
		model.tangents.reserve(model.positions.size());
		for (uint i = 0; i < model.positions.size(); ++i) {
			model.normals.emplace_back(0.0f, 1.0f, 0.0f);
			model.tangents.emplace_back(0.0f, 1.0f, 0.0f);
			model.uvs.emplace_back(0.0f, 0.0f);
		}

		return model;
	}

	IndexedModel IndexedModel::getIcosphereModel() {
		IndexedModel model;

		auto im = geometry::makeIcosphere(2);

		model.positions = im.first;
		model.indices = im.second;

		model.uvs.reserve(model.positions.size());
		model.normals.reserve(model.positions.size());
		model.tangents.reserve(model.positions.size());
		for (uint i = 0; i < model.positions.size(); ++i) {
			model.normals.emplace_back(0.0f, 1.0f, 0.0f);
			model.tangents.emplace_back(0.0f, 1.0f, 0.0f);
			model.uvs.emplace_back(0.0f, 0.0f);
		}

		return model;
	}

}
