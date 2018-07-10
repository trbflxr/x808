//
// Created by FLXR on 7/10/2018.
//

#ifndef X808_INDEXEDMODEL_HPP
#define X808_INDEXEDMODEL_HPP


#include <vector>
#include "xeint.hpp"
#include "common.hpp"
#include "math/math.hpp"

struct aiMesh;

namespace xe { namespace gfx {

	struct XE_API IndexedModel {
		std::vector<vec3> positions;
		std::vector<vec2> uvs;
		std::vector<vec3> normals;
		std::vector<uint> indices;

		explicit IndexedModel(const aiMesh *mesh);
	};

}}


#endif //X808_INDEXEDMODEL_HPP