//
// Created by FLXR on 9/20/2018.
//

#include <xe/math/math.hpp>
#include <xe/math/triangulator.hpp>

namespace xe {

#define CONCAVE -1
#define CONVEX 1

	void triangulator::compute(const std::vector<vec2> &vertices, std::vector<uint> &triangleIndices) {
		const uint count = (uint) vertices.size();

		std::vector<uint> indices(count);
		if (areVerticesClockwise(vertices.data(), count)) {
			for (uint i = 0; i < count; ++i) {
				indices[i] = i;
			}
		} else {
			for (uint i = 0, n = count - 1; i < count; ++i) {
				indices[i] = n - i;
			}
		}

		std::vector<int32> types(count);
		for (uint i = 0; i < count; ++i) {
			types[i] = classifyVertex(vertices.data(), indices.data(), i, count);
		}

		triangleIndices.reserve(__max(0, count - 2) * 3);
		triangulate(types, vertices.data(), indices, triangleIndices, count);
	}

	void triangulator::triangulate(std::vector<int32> &types, const vec2 *vertices, std::vector<uint> &indices,
	                               std::vector<uint> &triangles, uint count) {

		uint vertexCount = count;

		while (vertexCount > 3) {
			uint earTipIndex = findEarTip(types.data(), vertices, indices.data(), vertexCount);
			cutEarTip(types, indices, triangles, earTipIndex, vertexCount);

			const uint prevIndex_ = previousIndex(earTipIndex, vertexCount);
			const uint nextIndex_ = earTipIndex == vertexCount ? 0 : earTipIndex;
			types[prevIndex_] = classifyVertex(vertices, indices.data(), prevIndex_, vertexCount);
			types[nextIndex_] = classifyVertex(vertices, indices.data(), nextIndex_, vertexCount);
		}

		if (vertexCount == 3) {
			triangles.push_back(indices[0]);
			triangles.push_back(indices[1]);
			triangles.push_back(indices[2]);
		}
	}

	bool triangulator::areVerticesClockwise(const vec2 *vertices, uint count) {
		if (count < 2) return false;
		float area = 0.0f;
		vec2 p1;
		vec2 p2;
		for (uint i = 1; i < count; ++i) {
			p1 = vertices[i - 1];
			p2 = vertices[i];
			area += p1.x * p2.y - p2.x * p1.y;
		}
		p1 = vertices[count - 1];
		p2 = vertices[0];
		return area + p1.x * p2.y - p2.x * p1.y < 0;
	}

	int32 triangulator::classifyVertex(const vec2 *vertices, const uint *indices, uint index, uint count) {
		uint previous = indices[previousIndex(index, count)];
		uint current = indices[index];
		uint next = indices[nextIndex(index, count)];
		return computeSpannedAreaSign(vertices[previous], vertices[current], vertices[next]);
	}

	int32 triangulator::computeSpannedAreaSign(const vec2 &p1, const vec2 &p2, const vec2 &p3) {
		float area = p1.x * (p3.y - p2.y);
		area += p2.x * (p1.y - p3.y);
		area += p3.x * (p2.y - p1.y);
		return (int32) math::signum(area);
	}

	uint triangulator::findEarTip(const int32 *types, const vec2 *vertices, const uint *indices, uint count) {
		for (uint i = 0; i < count; i++) {
			if (isEarTip(types, vertices, indices, i, count)) return i;
		}

		for (uint i = 0; i < count; i++) {
			if (types[i] != CONCAVE) return i;
		}
		return 0;
	}

	bool triangulator::isEarTip(const int32 *types, const vec2 *vertices, const uint *indices, uint index, uint count) {
		if (types[index] == CONCAVE) return false;

		const uint prevIndex_ = previousIndex(index, count);
		const uint nextIndex_ = nextIndex(index, count);

		const uint ip1 = indices[prevIndex_];
		const uint ip2 = indices[index];
		const uint ip3 = indices[nextIndex_];

		const vec2 p1 = vertices[ip1];
		const vec2 p2 = vertices[ip2];
		const vec2 p3 = vertices[ip3];

		for (uint i = nextIndex(nextIndex_, count); i != prevIndex_; i = nextIndex(i, count)) {
			if (types[i] != CONVEX) {
				const uint v = indices[i];
				const vec2 vert = vertices[v];

				if (computeSpannedAreaSign(p3, p1, vert) >= 0) {
					if (computeSpannedAreaSign(p1, p2, vert) >= 0) {
						if (computeSpannedAreaSign(p2, p3, vert) >= 0) return false;
					}
				}
			}
		}
		return true;
	}

	void triangulator::cutEarTip(std::vector<int32> &types, std::vector<uint> &indices, std::vector<uint> &triangles,
	                             uint index, uint &count) {

		triangles.push_back(indices[previousIndex(index, count)]);
		triangles.push_back(indices[index]);
		triangles.push_back(indices[nextIndex(index, count)]);

		indices.erase(indices.begin() + index);
		types.erase(types.begin() + index);
		--count;
	}

}