//
// Created by FLXR on 3/2/2019.
//

#ifndef X808_MODEL_HPP
#define X808_MODEL_HPP


#include <vector>
#include <xe/gfx/mesh.hpp>
#include <xe/math/itransformable.hpp>

namespace xe {

	class XE_API Model : public Mesh, public ITransformable {
	public:
		explicit Model(const string &name, const IndexedModel &model);
		explicit Model(const string &name, const string &file);
		~Model() override;

	private:
		friend class ModelLoader;
	};

}

#endif //X808_MODEL_HPP
