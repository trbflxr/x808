//
// Created by FLXR on 7/9/2018.
//

#ifndef X808_MESH_HPP
#define X808_MESH_HPP


#include "gfx/api/vertexarray.hpp"
#include "gfx/api/indexbuffer.hpp"
#include "material.hpp"

namespace xe { namespace gfx {

	class Renderer3D;

	struct Vertex {
		vec3 position;
		vec2 uv;
		vec3 normal;

		Vertex(const vec3 &position, const vec2 &uv, const vec3 &normal = {0, 0, 0}) :
				position(position), uv(uv), normal(normal) { }
	};

	class XE_API Mesh {
	public:
		explicit Mesh(api::VertexArray *vertexArray,
		              api::IndexBuffer *indexBuffer,
		              MaterialInstance *materialInstance);

		Mesh(const Mesh &other);

		~Mesh();

		void render(Renderer3D *renderer);

		inline void setMaterial(MaterialInstance *material) { materialInstance = material; }
		inline MaterialInstance *getMaterial() const { return materialInstance; }

	private:
		api::VertexArray *vertexArray;
		api::IndexBuffer *indexBuffer;
		MaterialInstance *materialInstance;
	};

}}


#endif //X808_MESH_HPP
