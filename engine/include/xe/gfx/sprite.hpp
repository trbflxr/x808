//
// Created by FLXR on 9/12/2018.
//

#ifndef X808_SPRITE_HPP
#define X808_SPRITE_HPP


#include <array>
#include <xe/gfx/texture.hpp>
#include <xe/gfx/color.hpp>
#include <xe/math/vec2.hpp>

namespace xe {

	class Sprite {
	public:
		explicit XE_API Sprite(const Texture *texture,
		                       bool hasTransparency = false,
		                       uint color = color::WHITE,
		                       bool flipUVs = false,
		                       bool visible = true) noexcept;

		virtual ~Sprite() = default;

		const Texture *getTexture() const { return texture; }
		void setTexture(const Texture *texture) { Sprite::texture = texture; }

		bool hasTransparency() const { return hasTransparency_; }

		uint getColor() const { return color; }
		void setColor(uint color) { Sprite::color = color; }

		bool isVisible() const { return visible; }
		void setVisible(bool visible) { Sprite::visible = visible; }

		const std::array<vec2, 4> &getUVs() const { return UVs; }

		static inline const std::array<vec2, 4> &getDefaultUVs();
		static inline const std::array<vec2, 4> &getFlippedUVs();

	private:
		const Texture *texture;
		bool hasTransparency_;
		uint color;
		bool visible;
		std::array<vec2, 4> UVs;
	};

}


#endif //X808_SPRITE_HPP
