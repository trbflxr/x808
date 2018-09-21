//
// Created by FLXR on 9/18/2018.
//

#include <xe/gfx/2d/shape.hpp>

namespace xe {

	Shape::Shape(float layer) :
			IRenderable2D(layer),
			texture(nullptr) { }


	void Shape::setLayer(float layer) {
		IRenderable2D::layer = layer;

		if (!vertices.empty() && vertices[0].pos.z != layer) {
			for (auto &&v : vertices) {
				v.pos.z = layer;
			}
		}
	}

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
		const uint count = getPointCount();

		if (count < 3) {
			vertices.resize(0);
			indices.resize(0);
			return;
		}

		vertices.resize(count);

		//positions
		vertices[0].pos = vec3(getPoint(0), layer);

		//bounds
		float left = vertices[0].pos.x;
		float top = vertices[0].pos.y;
		float right = vertices[0].pos.x;
		float bottom = vertices[0].pos.y;

		//positions
		for (uint i = 1; i < count; ++i) {
			vertices[i].pos = vec3(getPoint(i), layer);

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
		const uint indicesCount = 3 * (count - 2);
		indices.resize(indicesCount);

		uint index = 0;
		for (uint i = 2; i < count; ++i) {
			indices[index++] = 0;
			indices[index++] = i - 1;
			indices[index++] = i;
		}
	}

	void Shape::updateUVs() {
		for (uint i = 0; i < getPointCount(); ++i) {
			if (texture) {
				const float xRatio = bounds.width > 0.0f ? (vertices[i].pos.x - bounds.x) / bounds.width : 0.0f;
				const float yRatio = bounds.height > 0.0f ? (vertices[i].pos.y - bounds.y) / bounds.height : 0.0f;

				vertices[i].uv.x = (textureRect.x + textureRect.width * xRatio) / texture->getWidth();
				vertices[i].uv.y = 1.0f - (textureRect.y + textureRect.height * yRatio) / texture->getHeight();
			} else {
				vertices[i].uv.x = 0.0f;
				vertices[i].uv.y = 0.0f;
			}
		}
	}

}
