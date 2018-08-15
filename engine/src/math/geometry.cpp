//
// Created by FLXR on 8/15/2018.
//

#include "geometry.hpp"
#include "math.hpp"

namespace xe {

	struct Triangle {
		uint vertex[3]{ };

		Triangle(uint x, uint y, uint z) {
			vertex[0] = x;
			vertex[1] = y;
			vertex[2] = z;
		}
	};


	/// ---- icosphere stuff ---- ///
	static constexpr float ICOS_X = 0.52573f;
	static constexpr float ICOS_Z = 0.85065f;
	static constexpr float ICOS_N = 0.0f;

	using TriangleList = std::vector<Triangle>;
	using VertexList = std::vector<vec3>;
	using Lookup = std::map<std::pair<uint, uint>, uint>;

	static const VertexList ICOS_VERTICES = {
			{-ICOS_X, ICOS_N,  ICOS_Z},
			{ICOS_X,  ICOS_N,  ICOS_Z},
			{-ICOS_X, ICOS_N,  -ICOS_Z},
			{ICOS_X,  ICOS_N,  -ICOS_Z},
			{ICOS_N,  ICOS_Z,  ICOS_X},
			{ICOS_N,  ICOS_Z,  -ICOS_X},
			{ICOS_N,  -ICOS_Z, ICOS_X},
			{ICOS_N,  -ICOS_Z, -ICOS_X},
			{ICOS_Z,  ICOS_X,  ICOS_N},
			{-ICOS_Z, ICOS_X,  ICOS_N},
			{ICOS_Z,  -ICOS_X, ICOS_N},
			{-ICOS_Z, -ICOS_X, ICOS_N}
	};

	static const TriangleList ICOS_TRIANGLES = {
			{0,  4,  1},
			{0,  9,  4},
			{9,  5,  4},
			{4,  5,  8},
			{4,  8,  1},
			{8,  10, 1},
			{8,  3,  10},
			{5,  3,  8},
			{5,  2,  3},
			{2,  7,  3},
			{7,  10, 3},
			{7,  6,  10},
			{7,  11, 6},
			{11, 0,  6},
			{0,  1,  6},
			{6,  1,  10},
			{9,  0,  11},
			{9,  11, 2},
			{9,  2,  5},
			{7,  2,  11}
	};

	uint vertexForEdge(Lookup &lookup, VertexList &vertices, uint first, uint second) {
		Lookup::key_type key(first, second);
		if (key.first > key.second) {
			std::swap(key.first, key.second);
		}

		auto inserted = lookup.insert({key, (uint) vertices.size()});

		if (inserted.second) {
			vec3 &edge0 = vertices[first];
			vec3 &edge1 = vertices[second];
			vec3 point = vec3::normalize(edge0 + edge1);

			vertices.push_back(point);
		}

		return inserted.first->second;
	}

	TriangleList subdivide(VertexList &vertices, TriangleList triangles) {
		Lookup lookup;
		TriangleList result;

		for (auto &&tri : triangles) {
			std::array<uint, 3> mid{ };

			for (int edge = 0; edge < 3; ++edge) {
				mid[edge] = vertexForEdge(lookup, vertices, tri.vertex[edge], tri.vertex[(edge + 1) % 3]);
			}

			result.emplace_back(tri.vertex[0], mid[0], mid[2]);
			result.emplace_back(tri.vertex[1], mid[1], mid[0]);
			result.emplace_back(tri.vertex[2], mid[2], mid[1]);
			result.emplace_back(mid[0], mid[1], mid[2]);
		}

		return result;
	}

	/// ---- generators ---- ///

	std::pair<std::vector<vec3>, std::vector<uint>> geometry::makeIcosphere(uint subdivisions) {
		VertexList vertices = ICOS_VERTICES;
		TriangleList triangles = ICOS_TRIANGLES;

		for (int i = 0; i < subdivisions; ++i) {
			triangles = subdivide(vertices, triangles);
		}

		std::vector<uint> indices(triangles.size() * 3);
		for (auto &&f : triangles) {
			indices.push_back(f.vertex[0]);
			indices.push_back(f.vertex[1]);
			indices.push_back(f.vertex[2]);
		}

		return {vertices, indices};
	}

	std::pair<std::vector<vec3>, std::vector<uint>>
	geometry::makeCone(float radius, float height, uint subdivisions) {
		std::vector<vec3> vertices(subdivisions + 2);
		std::vector<uint> indices(subdivisions * 2 * 3);

		vertices[0] = vec3(0.0f);
		for (uint i = 0, n = subdivisions - 1; i < subdivisions; ++i) {
			float ratio = (float) i / n;
			float r = ratio * XE_PI * 2.0f;
			float x = cosf(r) * radius;
			float z = sinf(r) * radius;

			vertices[i + 1] = vec3(x, 0.0f, z);
		}

		vertices[subdivisions + 1] = vec3(0.0f, height, 0.0f);

		// construct bottom
		for (uint i = 0, n = subdivisions - 1; i < n; i++) {
			uint offset = i * 3;
			indices[offset] = 0;
			indices[offset + 1] = i + 1;
			indices[offset + 2] = i + 2;
		}

		// construct sides
		int bottomOffset = subdivisions * 3;
		for (uint i = 0, n = subdivisions - 1; i < n; i++) {
			uint offset = i * 3 + bottomOffset;
			indices[offset] = i + 1;
			indices[offset + 1] = subdivisions + 1;
			indices[offset + 2] = i + 2;
		}

		return {vertices, indices};
	}

}