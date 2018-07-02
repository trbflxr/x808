//
// Created by FLXR on 7/1/2018.
//

#ifndef X808_SPRITECOMPONENT_HPP
#define X808_SPRITECOMPONENT_HPP


#include "gfx/api/texture2d.hpp"
#include "gfx/api/shader.hpp"
#include "gfx/renderable2d.hpp"

namespace xe { namespace gfx {
	class Renderer2D;
}}

namespace xe {

	class XE_API Sprite : public gfx::Renderable2D {
	public:
		explicit Sprite(gfx::Renderer2D *renderer, const vec2 &size, const gfx::api::Texture2D *texture);

		explicit Sprite(gfx::Renderer2D *renderer, const vec2 &size, uint color = color::WHITE);

	protected:
		void renderInternal(const gfx::api::Shader *shader) override;

	private:
		gfx::Renderer2D *renderer;
	};

}


#endif //X808_SPRITECOMPONENT_HPP
