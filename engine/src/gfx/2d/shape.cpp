//
// Created by FLXR on 9/18/2018.
//

#include <xe/gfx/2d/shape.hpp>

namespace xe {

	Shape::Shape() :
			texture(nullptr) { }


	void Shape::setTexture(const xe::Texture *texture) {
		Shape::texture = texture;

		if (texture) {
			setTextureRect(rect(0.0f, 0.0f, texture->getWidth(), texture->getHeight()));
		}
	}

	void Shape::setTextureRect(const rect &rect) {
		Shape::textureRect = rect;
		updateUVs();
	}

	void Shape::update() {
		const float z = getZ();

		uint count = getPointCount();
		uint indicesCount = getIndicesCount();

		if (count < 3) {
			vertices.resize(0);
			indices.resize(0);
			return;
		}

		vertices.resize(count);
		indices.resize(indicesCount);

		//positions
		vertices[0].pos = vec3(getPoint(0), z);

		//bounds
		float left = vertices[0].pos.x;
		float top = vertices[0].pos.y;
		float right = vertices[0].pos.x;
		float bottom = vertices[0].pos.y;

		//positions
		for (uint i = 1; i < count; ++i) {
			vertices[i].pos = vec3(getPoint(i), z);

			if (vertices[i].pos.x < left) {
				left = vertices[i].pos.x;
			} else if (vertices[i].pos.x > right) {
				right = vertices[i].pos.x;
			}

			if (vertices[i].pos.y < top) {
				top = vertices[i].pos.y;
			} else if (vertices[i].pos.y > bottom) {
				bottom = vertices[i].pos.y;
			}
		}

		//update bounds
		bounds = rect(left, top, right - left, bottom - top);

		updateUVs();

		//update indices
		uint index = 0;
		for (uint i = 2; i < count; ++i) {
			indices[index++] = 0;
			indices[index++] = i - 1;
			indices[index++] = i;
		}
	}

	void Shape::updateUVs() {
		for (uint i = 0; i < getPointCount(); ++i) {
			const float xRatio = bounds.width > 0.0f ? (vertices[i].pos.x - bounds.x) / bounds.width : 0.0f;
			const float yRatio = bounds.height > 0.0f ? (vertices[i].pos.y - bounds.y) / bounds.height : 0.0f;

			vertices[i].uv.x = (textureRect.x + textureRect.width * xRatio) / textureRect.width;
			vertices[i].uv.y = (textureRect.y + textureRect.height * yRatio) / textureRect.height;
		}
	}

}
