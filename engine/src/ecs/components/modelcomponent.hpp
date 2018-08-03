//
// Created by FLXR on 7/25/2018.
//

#ifndef X808_MODELCOMPONENT_HPP
#define X808_MODELCOMPONENT_HPP


#include "ecs/ecscomponent.hpp"
#include "gfx/mesh.hpp"
#include "gfx/material.hpp"

namespace xe {

	struct ModelComponent : public ECSComponent<ModelComponent> {
		Mesh *mesh;
		Material *material;

		ModelComponent() noexcept : mesh(nullptr), material(nullptr) { }
		explicit ModelComponent(Mesh *mesh, Material *material) : mesh(mesh), material(material) { }
	};

}


#endif //X808_MODELCOMPONENT_HPP
