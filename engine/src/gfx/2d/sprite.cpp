//
// Created by FLXR on 9/12/2018.
//

#include <xe/gfx/2d/sprite.hpp>
#include <xe/utils/logger.hpp>

namespace xe {

	Sprite::Sprite(const Texture *texture) :
			IRenderable2D() {

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

	Sprite::Sprite(const Sprite &other) :
			IRenderable2D(other),
			ITransformable2D(other),
			vertices(other.vertices),
			indices(other.indices),
			textureRect(other.textureRect),
			texture(other.texture) { }

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

	void Sprite::update() {
		//bounds
		const float width = fabsf(textureRect.width);
		const float height = fabsf(textureRect.height);
		const rect bounds(0.0f, 0.0f, width, height);

		//positions
		vertices[0].pos = vec2(0.0f, 0.0f);
		vertices[1].pos = vec2(bounds.width, 0.0f);
		vertices[2].pos = vec2(bounds.width, bounds.height);
		vertices[3].pos = vec2(0.0f, bounds.height);

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