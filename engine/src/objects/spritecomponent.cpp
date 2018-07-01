//
// Created by FLXR on 7/1/2018.
//

#include "spritecomponent.hpp"
#include "gfx/renderer2d.hpp"

xe::SpriteComponent::SpriteComponent(xe::gfx::Renderer2D *renderer,
                                     const xe::vec2 &size,
                                     const xe::gfx::api::Texture2D *texture) :
		Renderable2D(size, color::WHITE),
		renderer(renderer) {

	Renderable2D::texture = texture;
}

xe::SpriteComponent::SpriteComponent(xe::gfx::Renderer2D *renderer,
                                     const xe::vec2 &size,
                                     uint color) :
		Renderable2D(size, color),
		renderer(renderer) {}


void xe::SpriteComponent::renderInternal(const xe::gfx::api::Shader *shader)  {
	renderer->submit(this);
}
