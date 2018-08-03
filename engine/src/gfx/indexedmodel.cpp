//
// Created by FLXR on 7/10/2018.
//

#include <assimp/mesh.h>
#include "indexedmodel.hpp"

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

}