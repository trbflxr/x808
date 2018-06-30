//
// Created by FLXR on 6/30/2018.
//

#include "sprite.hpp"

xe::gfx::Sprite::Sprite() : Renderable2D() { }

xe::gfx::Sprite::Sprite(xe::gfx::api::Texture2D *texture) :
		Renderable2D({0, 0}, vec2(texture->getWidth(), texture->getHeight()), color::WHITE) {

	Renderable2D::texture = texture;
}

xe::gfx::Sprite::Sprite(float x, float y, xe::gfx::api::Texture2D *texture) :
		Renderable2D({x, y}, vec2(texture->getWidth(), texture->getHeight()), color::WHITE) {

	Renderable2D::texture = texture;
}

xe::gfx::Sprite::Sprite(float x, float y, float width, float height, uint color) :
		Renderable2D({x, y}, {width, height}, color) {
}

xe::gfx::Sprite::Sprite(float x, float y, float width, float height, xe::gfx::api::Texture *texture) :
		Renderable2D({x, y}, {width, height}, color::WHITE) {

	Renderable2D::texture = texture;
}

void xe::gfx::Sprite::setUVs(const std::vector<xe::vec2> &uvs) {
	UVs = uvs;
}
