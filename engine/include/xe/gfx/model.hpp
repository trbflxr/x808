//
// Created by FLXR on 3/2/2019.
//

#ifndef X808_MODEL_HPP
#define X808_MODEL_HPP


#include <vector>
#include <xe/gfx/mesh.hpp>
#include <xe/math/itransformable.hpp>

namespace xe {

	class XE_API Model : public ITransformable {
	public:
		explicit Model(const std::vector<const Mesh *> &meshes);
		explicit Model(const Mesh *mesh);
		~Model() override;

		void render(BeginMode mode) const;

		inline const std::vector<const Mesh *> &getMeshes() const { return meshes; }

	private:
		std::vector<const Mesh *> meshes;
	};

}

#endif //X808_MODEL_HPP
