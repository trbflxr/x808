//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_UNIQUEMESH_HPP
#define X808_UNIQUEMESH_HPP


#include "mesh1.hpp"

namespace xe {

	class UniqueMesh {
	public:
		mat4 baseTransformation;
		mat4 transformation;
		mat4 prevTransformation;

		Mesh1 *mesh;

	public:
		explicit UniqueMesh(const std::string_view &id, Mesh1 *mesh, const mat4 &transformation) :
				id(id),
				mesh(mesh),
				baseTransformation(transformation),
				transformation(transformation),
				prevTransformation(transformation) { }

		~UniqueMesh() {
			delete mesh;
		}

		const std::string &getId() const { return id; }

	private:
		std::string id;
	};

}


#endif //X808_UNIQUEMESH_HPP
