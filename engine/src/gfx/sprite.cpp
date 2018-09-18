//
// Created by FLXR on 9/12/2018.
//

#include <xe/gfx/sprite.hpp>
#include <xe/utils/log.hpp>

namespace xe {

	Sprite::Sprite(const Texture *texture, bool flipUVs) {
		XE_ASSERT(false, "Not implemented");

		vertices = new Vertex2D[4];
		indices = new uint[6];

		for (uint i = 0; i < 4; ++i) {
			vertices[i].uv = flipUVs ? getFlippedUVs()[i] : getDefaultUVs()[i];
		}

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;

		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;

		updateVertices();

//		setTexture(texture);
	}

	Sprite::~Sprite() {
		delete[] vertices;
		delete[] indices;
	}

	void Sprite::updateVertices() {
//		const vec2 size = vec2(texture->getWidth(), texture->getHeight());
//		const float z = getZ();
//
//		vertices[0].pos = {0.0f, 0.0f, z};
//		vertices[1].pos = {size.x, 0.0f, z};
//		vertices[2].pos = {size.x, size.y, z};
//		vertices[3].pos = {0.0f, size.y, z};
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
}