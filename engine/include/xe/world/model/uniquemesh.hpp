//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_UNIQUEMESH_HPP
#define X808_UNIQUEMESH_HPP


#include <xe/world/model/mesh.hpp>

namespace xe {

	class UniqueMesh {
	public:
		mat4 baseTransformation;
		mat4 transformation;
		mat4 prevTransformation;

		Mesh *mesh;

	public:
		explicit UniqueMesh(const string &id, Mesh *mesh, const mat4 &transformation) :
				id(id),
				mesh(mesh),
				baseTransformation(transformation),
				transformation(transformation),
				prevTransformation(transformation) { }

		~UniqueMesh() {
			delete mesh;
		}

		const string &getId() const { return id; }

	private:
		string id;
	};

}


#endif //X808_UNIQUEMESH_HPP
