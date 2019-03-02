//
// Created by FLXR on 3/2/2019.
//

#include <xe/gfx/model.hpp>

namespace xe {

	Model::Model(const std::vector<const Mesh *> &meshes) :
			meshes(meshes) { }

	Model::Model(const Mesh *mesh) {
		meshes.push_back(mesh);
	}

	Model::~Model() {
		for (const auto &m : meshes) {
			delete m;
		}
		meshes.clear();
	}

	void Model::render(BeginMode mode) const {
		for (const auto &m : meshes) {
			m->render(mode);
		}
	}

}