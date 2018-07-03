//
// Created by FLXR on 7/1/2018.
//

#include "sprite.hpp"

xe::gfx::Sprite::Sprite(const xe::vec2 &position, const xe::vec2 &size, float rotation,
                        const xe::gfx::api::Texture *texture, uint color) :
		Renderable2D(position, size, rotation, color) {

	Renderable2D::texture = texture;
}
