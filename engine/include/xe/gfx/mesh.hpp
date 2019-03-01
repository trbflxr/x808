//
// Created by FLXR on 3/1/2019.
//

#ifndef X808_MESH_HPP
#define X808_MESH_HPP


#include <xe/common.hpp>
#include <xe/string.hpp>
#include <xe/gfx/indexedmodel.hpp>
#include <xe/gfx/indexbuffer.hpp>
#include <xe/gfx/vertexarray.hpp>

namespace xe {

	class XE_API Mesh {
	public:
		struct Vertex3D {
			vec3 pos;
			vec3 normal;
			vec3 tangent;
			vec2 uv;
		};

	public:
		explicit Mesh(const string &name, const IndexedModel &model);
		virtual ~Mesh();

		void render(BeginMode mode) const;

		inline const string &getName() const { return name; }
		inline const VertexArray *getVao() const { return vao; }
		inline const IndexBuffer *getIbo() const { return ibo; }

		static Mesh *spotLightMesh(const string &name);
		static Mesh *pointLightMesh(const string &name);

	private:
		string name;

		VertexArray *vao;
		IndexBuffer *ibo;
	};

}


#endif //X808_MESH_HPP
