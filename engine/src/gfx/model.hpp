//
// Created by FLXR on 7/10/2018.
//

#ifndef X808_MODEL_HPP
#define X808_MODEL_HPP


#include "indexedmodel.hpp"
#include "mesh.hpp"

namespace xe { namespace gfx {

	class XE_API Model {
	public:
		explicit Model(IndexedModel &model, MaterialInstance *materialInstance = nullptr);
		~Model();

		void render(Renderer3D *renderer);

		inline Mesh *getMesh() const { return mesh; }

	private:
		Mesh *mesh;
	};

}}


#endif //X808_MODEL_HPP
