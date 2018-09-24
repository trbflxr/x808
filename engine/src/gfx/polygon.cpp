//
// Created by FLXR on 9/18/2018.
//

#include <xe/math/triangulator.hpp>
#include <xe/gfx/polygon.hpp>
#include <algorithm>

namespace xe {

	Polygon::Polygon(float layer) :
			IRenderable2D(layer),
			pointsChanged(false),
			texture(nullptr) { }

	Polygon::Polygon(const std::vector<vec2> &points, float layer) :
			IRenderable2D(layer),
			points(points),
			pointsChanged(true),
			texture(nullptr) {

		create();
	}

	void Polygon::create() {
		if (points.size() < 3) return;

		pointsChanged = true;

		indices.clear();
		triangulator::compute(points, indices);

		std::reverse(indices.begin(), indices.end());

		vertices.resize(points.size());
		for (uint i = 0; i < points.size(); ++i) {
			vertices[i].pos = vec3(points[i], layer);
		}

		updateUVs();
	}

	void Polygon::reshape(const std::vector<vec2> &points) {
		Polygon::points = points;
		create();
	}

	void Polygon::setTexture(const Texture *texture) {
		Polygon::texture = texture;

		if (texture) {
			setTextureRect(rect(0.0f, 0.0f, texture->getWidth(), texture->getHeight()));
		}
	}

	void Polygon::setLayer(float layer) {
		IRenderable2D::layer = layer;

		if (!vertices.empty() && vertices[0].pos.z != layer) {
			for (auto &&v : vertices) {
				v.pos.z = layer;
			}
		}
	}

	void Polygon::setTextureRect(const rect &rect) {
		Polygon::textureRect = rect;
		updateUVs();
	}

	void Polygon::updateUVs() {
		if (texture) {
			const float invTexWidth = 1.0f / texture->getWidth();
			const float invTexHeight = 1.0f / texture->getHeight();
			const float u0 = textureRect.x * invTexWidth;
			const float v0 = textureRect.y * invTexHeight;
			const float u1 = (textureRect.x + textureRect.width) * invTexWidth;
			const float v1 = (textureRect.y + textureRect.height) * invTexHeight;
			const float uvWidth = u1 - u0;
			const float uvHeight = v1 - v0;
			const float width = roundf(fabsf(uvWidth) * texture->getWidth());
			const float height = roundf(fabsf(uvHeight) * texture->getHeight());

			for (auto &&v : vertices) {
				v.uv.x = u0 + uvWidth * (v.pos.x / width);
				v.uv.y = v0 + uvHeight * (1.0f - v.pos.y / height);
			}
		}
	}

}
