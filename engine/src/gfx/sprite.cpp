//
// Created by FLXR on 7/1/2018.
//

#include "sprite.hpp"

xe::gfx::Sprite::Sprite(const xe::vec2 &position, float z, const xe::vec2 &size, float rotation,
                        const xe::gfx::api::Texture *texture, uint color) :
		Renderable2D(position, z, size, rotation, color) {

	Renderable2D::texture = texture;
}
