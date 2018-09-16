//
// Created by FLXR on 9/13/2018.
//

#include <xe/gfx/sprite.hpp>
#include <xe/gfx/rectangleshape.hpp>

namespace xe {

	RectangleShape::RectangleShape(const vec2 &size) :
			size(size),
			sizeChanged(true) {

		vertices = new Vertex2D[4];
		indices = new uint[6];

		const auto &UVs = Sprite::getDefaultUVs();
		for (uint i = 0; i < 4; ++i) {
			vertices[i].uv = UVs[i];
		}

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;

		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;
	}

	RectangleShape::~RectangleShape() {
		delete[] vertices;
		delete[] indices;
	}

	void RectangleShape::setSize(const vec2 &size) {
		RectangleShape::size = size;
		setDirty(true);
		sizeChanged = true;
	}

	const Vertex2D *RectangleShape::getVertices() const {
		if (isDirty()) {
			setDirty(false);

			const vec3 &pos = getPosition();
			const float rot = getRotation();

			const float localX = -size.x / 2.0f;
			const float localY = -size.y / 2.0f;
			const float localX2 = localX + size.x;
			const float localY2 = localY + size.y;
			const float worldOriginX = pos.x - localX;
			const float worldOriginY = pos.y - localY;

			const float cos = cosf(to_rad(rot));
			const float sin = sinf(to_rad(rot));
			const float localXCos = localX * cos;
			const float localXSin = localX * sin;
			const float localYCos = localY * cos;
			const float localYSin = localY * sin;
			const float localX2Cos = localX2 * cos;
			const float localX2Sin = localX2 * sin;
			const float localY2Cos = localY2 * cos;
			const float localY2Sin = localY2 * sin;

			vertices[0].pos = {localXCos - localYSin + worldOriginX, localYCos + localXSin + worldOriginY, pos.z};
			vertices[3].pos = {localXCos - localY2Sin + worldOriginX, localY2Cos + localXSin + worldOriginY, pos.z};
			vertices[2].pos = {localX2Cos - localY2Sin + worldOriginX, localY2Cos + localX2Sin + worldOriginY, pos.z};
			vertices[1].pos = {vertices[0].pos.x + (vertices[2].pos.x - vertices[3].pos.x),
			                   vertices[2].pos.y - (vertices[3].pos.y - vertices[0].pos.y),
			                   pos.z};
		}

		return vertices;
	}

}