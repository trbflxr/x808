//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_UNIQUEMESH_HPP
#define X808_UNIQUEMESH_HPP


#include <xe/gameobject.hpp>
#include <xe/world/model/mesh.hpp>

namespace xe {

	class UniqueMesh : public GameObject {
	public:
		Mesh *mesh;

	public:
		explicit UniqueMesh(const string &id, Mesh *mesh, const mat4 &transformation) :
				GameObject(transformation),
				id(id),
				mesh(mesh) { }

		~UniqueMesh() {
			delete mesh;
		}

		const string &getId() const { return id; }

	private:
		string id;
	};

}


#endif //X808_UNIQUEMESH_HPP
