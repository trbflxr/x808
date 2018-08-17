//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_MESH1_HPP
#define X808_MESH1_HPP


#include <string>
#include <vector>

#include <xe/common.hpp>
#include <xe/gfx/indexedmodel.hpp>
#include <xe/gfx/indexbuffer.hpp>
#include <xe/gfx/vertexbuffer.hpp>
#include <xe/gfx/vertexarray.hpp>
#include <xe/world/model/material.hpp>

namespace xe {

	class XE_API Mesh {
	public:
		struct Vertex {
			vec3 position;
			vec3 normal;
			vec3 tangent;
			vec2 uv;
		};

	public:
		explicit Mesh(const string &id);
		explicit Mesh(const string &id, const IndexedModel &model, Material *material);
		~Mesh();

		void render(BeginMode mode) const;

		const string &getId() const { return id; }
		VertexArray *getVertexArray() const { return vertexArray; }
		IndexBuffer *getIndexBuffer() const { return indexBuffer; }
		Material *getMaterial() const { return material; }

		static Mesh *spotLightMesh();
		static Mesh *pointLightMesh();

	private:
		void initMesh(const IndexedModel &model);

	private:
		string id;

		VertexArray *vertexArray;
		IndexBuffer *indexBuffer;

		Material *material;
	};

}

#endif //X808_MESH1_HPP
