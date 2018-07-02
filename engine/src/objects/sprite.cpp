//
// Created by FLXR on 7/1/2018.
//

#include "sprite.hpp"
#include "gfx/renderer2d.hpp"

xe::Sprite::Sprite(gfx::Renderer2D *renderer, const vec2 &size, const gfx::api::Texture2D *texture) :
		Renderable2D(size, color::WHITE),
		renderer(renderer) {

	Renderable2D::texture = texture;
}

xe::Sprite::Sprite(gfx::Renderer2D *renderer, const vec2 &size, uint color) :
		Renderable2D(size, color),
		renderer(renderer) { }


void xe::Sprite::renderInternal(const xe::gfx::api::Shader *shader) {
	renderer->submit(this);
}
