//
// Created by FLXR on 9/12/2018.
//

#include <xe/gfx/sprite.hpp>

namespace xe {

	Sprite::Sprite(const Texture *texture, bool hasTransparency, uint color, bool flipUVs, bool visible) noexcept :
			IRenderable2D(hasTransparency, visible),
			texture(texture),
			color(color) {

		vertices.reserve(4);

		for (uint i = 0; i < 4; ++i) {
			vertices[i].uv = flipUVs ? getFlippedUVs()[i] : getDefaultUVs()[i];
		}

	}

	const std::vector<vec2> &Sprite::getDefaultUVs() {
		static std::vector<vec2> UVs{
				vec2(0, 1),
				vec2(1, 1),
				vec2(1, 0),
				vec2(0, 0)
		};
		return UVs;
	}

	const std::vector<vec2> &Sprite::getFlippedUVs() {
		static std::vector<vec2> UVs{
				vec2(0, 0),
				vec2(1, 0),
				vec2(1, 1),
				vec2(0, 1)
		};
		return UVs;
	}

	const std::vector<Vertex2D> &Sprite::getVertices() const {
		if (isDirty()) {
			setDirty(false);

			const vec2 &size = getSize();
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