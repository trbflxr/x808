//
// Created by FLXR on 7/13/2018.
//

#ifndef X808_MODEL_HPP
#define X808_MODEL_HPP


#include "material.hpp"
#include "mesh.hpp"
#include "math/transform.hpp"

namespace xe { namespace gfx {

	struct Model {
		Mesh *mesh;
		Material *material;
		Transform transform;

		Model() = default;
		explicit Model(Mesh *mesh, Material *material) :
				mesh(mesh), material(material), transform() { }
	};

}}


#endif //X808_MODEL_HPP
