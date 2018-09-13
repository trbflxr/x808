//
// Created by FLXR on 9/12/2018.
//

#ifndef X808_SPRITE_HPP
#define X808_SPRITE_HPP


#include <array>
#include <xe/gfx/texture.hpp>
#include <xe/gfx/color.hpp>
#include <xe/gfx/2d/irenderable2d.hpp>
#include <xe/gfx/2d/itransformable2d.hpp>

namespace xe {

	class Sprite : public IRenderable2D, public ITransformable2D {
	public:
		explicit XE_API Sprite(const Texture *texture,
		                       bool hasTransparency = false,
		                       uint color = color::WHITE,
		                       bool flipUVs = false,
		                       bool visible = true) noexcept;

		const Texture *getTexture() const override { return texture; }
		void setTexture(const Texture *texture) { Sprite::texture = texture; }

		bool hasTransparency() const override { return hasTransparency_; }

		uint getColor() const override { return color; }
		void setColor(uint color) { Sprite::color = color; }

		bool isVisible() const override { return visible; }
		void setVisible(bool visible) { Sprite::visible = visible; }

		const std::array<vec2, 4> &getUVs() const override { return UVs; }

		const std::array<vec3, 4> &getVertices() const override { return transform.getVertices(); }
		const vec3 &getPosition() const override { return transform.getPosition(); }

		static const std::array<vec2, 4> &getDefaultUVs();
		static const std::array<vec2, 4> &getFlippedUVs();

	private:
		const Texture *texture;
		bool hasTransparency_;
		uint color;
		bool visible;
		std::array<vec2, 4> UVs;
	};

}


#endif //X808_SPRITE_HPP
