//
// Created by FLXR on 7/12/2018.
//

#ifndef X808_MESH_HPP
#define X808_MESH_HPP


#include <string>
#include "gfx/api/indexbuffer.hpp"
#include "gfx/api/vertexarray.hpp"
#include "indexedmodel.hpp"

namespace xe {

	struct MeshVertexData {
		vec3 position;
		vec2 uv;
		vec3 normal;
		vec3 tangent;
	};

	class XE_API Mesh {
	public:
		explicit Mesh(const IndexedModel &model);
		explicit Mesh(const std::string_view &path);
		~Mesh();

		void render() const;

		static Mesh *createPlaneMesh();

	private:
		void initMesh(const IndexedModel &model);

	private:
		api::VertexArray *vertexArray;
		api::IndexBuffer *indexBuffer;
		uint indicesSize;
	};


}

#endif //X808_MESH_HPP
