//
// Created by FLXR on 7/10/2018.
//

#ifndef X808_INDEXEDMODEL_HPP
#define X808_INDEXEDMODEL_HPP


#include <vector>
#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/math/vec3.hpp>

struct aiMesh;

namespace xe {

	struct XE_API IndexedModel {
		std::vector<vec3> positions;
		std::vector<vec2> uvs;
		std::vector<vec3> normals;
		std::vector<vec3> tangents;
		std::vector<uint> indices;

		IndexedModel() = default;
		explicit IndexedModel(const aiMesh *mesh);

		static IndexedModel &getConeModel();
		static IndexedModel &getIcosphereModel();
	};

}


#endif //X808_INDEXEDMODEL_HPP
