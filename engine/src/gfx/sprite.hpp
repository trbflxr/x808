//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_SPRITE_HPP
#define X808_SPRITE_HPP


#include "renderable2d.hpp"
#include "gfx/api/texture2d.hpp"

namespace xe { namespace gfx {

	class XE_API Sprite : public Renderable2D {
	public:
		explicit Sprite(api::Texture2D* texture);
		explicit Sprite(float x, float y, api::Texture2D* texture);
		explicit Sprite(float x, float y, float width, float height, uint color);
		explicit Sprite(float x, float y, float width, float height, api::Texture* texture);

		void setUVs(const std::vector<vec2> &uvs);

		inline void setTexture(api::Texture2D* texture) { Sprite::texture = texture; }

	protected:
		Sprite();
	};

}}


#endif //X808_SPRITE_HPP
