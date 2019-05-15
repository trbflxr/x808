//
// Created by FLXR on 7/10/2018.
//

#include <assimp/mesh.h>
#include <xe/gfx/indexedmodel.hpp>
#include <xe/math/math.hpp>
#include <xe/math/geometry.hpp>

namespace xe {

  IndexedModel::IndexedModel(const aiMesh *mesh) {

    bool hasUvs = false;
    bool hasNormals = false;
    bool hasTangents = false;

    if (mesh->HasPositions()) {
      positions.reserve(mesh->mNumVertices);
      for (uint i = 0; i < mesh->mNumVertices; ++i) {
        positions.emplace_back(mesh->mVertices[i].x,
                               mesh->mVertices[i].y,
                               mesh->mVertices[i].z);
      }
    }

    if (mesh->HasTextureCoords(0)) {
      hasUvs = true;
      uvs.reserve(mesh->mNumVertices);
      for (uint i = 0; i < mesh->mNumVertices; ++i) {
        uvs.emplace_back(mesh->mTextureCoords[0][i].x,
                         mesh->mTextureCoords[0][i].y);
      }
    }

    if (mesh->HasNormals()) {
      hasNormals = true;
      normals.reserve(mesh->mNumVertices);
      for (uint i = 0; i < mesh->mNumVertices; ++i) {
        normals.emplace_back(mesh->mNormals[i].x,
                             mesh->mNormals[i].y,
                             mesh->mNormals[i].z);
      }
    }

    if (mesh->HasTangentsAndBitangents()) {
      hasTangents = true;
      tangents.reserve(mesh->mNumVertices);
      for (uint i = 0; i < mesh->mNumVertices; ++i) {
        tangents.emplace_back(mesh->mTangents[i].x,
                              mesh->mTangents[i].y,
                              mesh->mTangents[i].z);
      }
    }

    if (mesh->HasFaces()) {
      indices.reserve(mesh->mNumFaces);
      for (uint i = 0; i < mesh->mNumFaces; ++i) {
        for (uint j = 0; j < mesh->mFaces[i].mNumIndices; ++j) {
          indices.push_back(mesh->mFaces[i].mIndices[j]);
        }
      }
    }

    if (hasUvs && hasNormals && hasTangents) return;

    uvs.reserve(mesh->mNumVertices);
    normals.reserve(mesh->mNumVertices);
    tangents.reserve(mesh->mNumVertices);
    for (uint i = 0; i < mesh->mNumVertices; ++i) {
      if (!hasUvs) uvs.emplace_back(0.0f, 0.0f);
      if (!hasNormals) normals.emplace_back(0.0f, 1.0f, 0.0f);
      if (!hasTangents) tangents.emplace_back(0.0f, 1.0f, 0.0f);
    }

  }

  IndexedModel &IndexedModel::getConeModel() {
    static const quat r = quat::rotation(90.0f, vec3::UnitX());

    static IndexedModel model;
    static bool initialized = false;
    if (initialized) return model;

    auto im = geometry::makeCone(2.0f, 4.0f, 15);

    model.positions = im.first;
    model.indices = im.second;

    model.uvs.reserve(model.positions.size());
    model.normals.reserve(model.positions.size());
    model.tangents.reserve(model.positions.size());
    for (uint i = 0; i < model.positions.size(); ++i) {
      model.positions[i] = model.positions[i].rotate(r);
      model.normals.emplace_back(0.0f, 1.0f, 0.0f);
      model.tangents.emplace_back(0.0f, 1.0f, 0.0f);
      model.uvs.emplace_back(0.0f, 0.0f);
    }

    initialized = true;
    return model;
  }

  IndexedModel &IndexedModel::getIcosphereModel() {
    static const quat r = quat::rotation(90.0f, vec3::UnitX());

    static IndexedModel model;
    static bool initialized = false;
    if (initialized) return model;

    auto im = geometry::makeIcosphere(2);

    model.positions = im.first;
    model.indices = im.second;

    model.uvs.reserve(model.positions.size());
    model.normals.reserve(model.positions.size());
    model.tangents.reserve(model.positions.size());
    for (uint i = 0; i < model.positions.size(); ++i) {
      model.positions[i] = model.positions[i].rotate(r);
      model.normals.emplace_back(0.0f, 1.0f, 0.0f);
      model.tangents.emplace_back(0.0f, 1.0f, 0.0f);
      model.uvs.emplace_back(0.0f, 0.0f);
    }

    initialized = true;
    return model;
  }

}
