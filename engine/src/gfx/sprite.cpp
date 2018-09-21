//
// Created by FLXR on 9/12/2018.
//

#include <xe/gfx/sprite.hpp>
#include <xe/utils/log.hpp>

namespace xe {

	Sprite::Sprite(const Texture *texture, float layer) :
			IRenderable2D(layer) {

		vertices = new Vertex2D[4];
		indices = new uint[6];

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;

		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;

		setTexture(texture);
	}

	Sprite::~Sprite() {
		delete[] vertices;
		delete[] indices;
	}

	void Sprite::setTexture(const Texture *texture) {
		Sprite::texture = texture;

		if (texture) {
			setTextureRect(rect(0.0f, 0.0f, texture->getWidth(), texture->getHeight()));
		}
	}

	void Sprite::setTextureRect(const rect &rect) {
		if (rect != textureRect) {
			Sprite::textureRect = rect;
			update();
		}
	}

	void Sprite::setLayer(float layer) {
		IRenderable2D::layer = layer;

		vertices[0].pos.z = layer;
		vertices[1].pos.z = layer;
		vertices[2].pos.z = layer;
		vertices[3].pos.z = layer;
	}

	void Sprite::update() {
		//bounds
		const float width = fabsf(textureRect.width);
		const float height = fabsf(textureRect.height);
		const rect bounds(0.f, 0.0f, width, height);

		//positions
		vertices[0].pos = vec3(0.0f, 0.0f, layer);
		vertices[1].pos = vec3(bounds.width, 0.0f, layer);
		vertices[2].pos = vec3(bounds.width, bounds.height, layer);
		vertices[3].pos = vec3(0.0f, bounds.height, layer);

		//uvs
		if (texture) {
			const float w = texture->getWidth();
			const float h = texture->getHeight();

			const float x = textureRect.x / w;
			const float mx = (x + textureRect.width) / w;
			const float y = textureRect.y / h;
			const float my = (y + textureRect.height) / h;

			vertices[0].uv = vec2(x, my);
			vertices[1].uv = vec2(mx, my);
			vertices[2].uv = vec2(mx, y);
			vertices[3].uv = vec2(x, y);
		}
	}

}