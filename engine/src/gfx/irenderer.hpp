//
// Created by FLXR on 8/4/2018.
//

#ifndef X808_IRENDERER_HPP
#define X808_IRENDERER_HPP


#include "material.hpp"
#include "mesh.hpp"
#include "math/transform.hpp"

namespace xe {

	class IRenderer {
	protected:
		struct RenderTarget {
			const Mesh *mesh;
			const Material *material;
			const Transform &transform;

			RenderTarget(const Mesh *mesh, const Material *material, const Transform &transform) noexcept :
					mesh(mesh), material(material), transform(transform) { }
		};
	};

}


#endif //X808_IRENDERER_HPP
