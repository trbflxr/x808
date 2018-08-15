//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_MESH1_HPP
#define X808_MESH1_HPP


#include <string>
#include <vector>

#include "common.hpp"
#include "math/math.hpp"
#include "material1.hpp"
#include "gfx/shader.hpp"
#include "gfx/indexedmodel.hpp"
#include "gfx/api/indexbuffer.hpp"
#include "gfx/api/vertexarray.hpp"

namespace xe {

	class XE_API Mesh1 {
	public:
		struct Vertex {
			vec3 position;
			vec3 normal;
			vec3 tangent;
			vec2 uv;
		};

	public:
		explicit Mesh1(const std::string_view &id);
		explicit Mesh1(const std::string_view &id, const IndexedModel &model, Material1 *material);
		~Mesh1();

		const std::string &getId() const { return id; }

		api::VertexArray *getVertexArray() const { return vertexArray; }
		api::IndexBuffer *getIndexBuffer() const { return indexBuffer; }
		Material1 *getMaterial() const { return material; }

		static Mesh1* spotLightMesh();
		static Mesh1* pointLightMesh();

	private:
		void initMesh(const IndexedModel &model);

	private:
		std::string id;

		api::VertexArray *vertexArray;
		api::IndexBuffer *indexBuffer;

		Material1 *material;
	};

}

#endif //X808_MESH1_HPP
