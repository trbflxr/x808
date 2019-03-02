//
// Created by FLXR on 3/2/2019.
//

#include <xe/gfx/model.hpp>
#include <xe/loaders/modelloader.hpp>

namespace xe {


	Model::Model(const string &name, const IndexedModel &model) :
			Mesh(name, model) { }

	Model::Model(const string &name, const string &file) :
			Mesh(name) {

		if (!ModelLoader::loadModel(this, file)) {
			init(IndexedModel::getIcosphereModel());
		}
	}

	Model::~Model() { }

}