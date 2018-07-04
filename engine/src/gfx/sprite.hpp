//
// Created by FLXR on 7/1/2018.
//

#ifndef X808_SPRITECOMPONENT_HPP
#define X808_SPRITECOMPONENT_HPP


#include "api/texture2d.hpp"
#include "renderable2d.hpp"

namespace xe { namespace gfx {

	class XE_API Sprite : public gfx::Renderable2D {
	public:
		explicit Sprite(const vec2 &position, float z, const vec2 &size, float rotation,
		                const api::Texture *texture, uint color = color::WHITE);
	};

}}


#endif //X808_SPRITECOMPONENT_HPP
