//
// Created by FLXR on 9/12/2018.
//

#ifndef X808_SPRITE_HPP
#define X808_SPRITE_HPP


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

		inline const Texture *getTexture() const override { return texture; }
		inline void setTexture(const Texture *texture) { Sprite::texture = texture; }

		uint getColor() const override { return color; }
		void setColor(uint color) { Sprite::color = color; }

		inline uint getVerticesSize() const override { return 4; }
		const std::vector<Vertex2D> &getVertices() const override;

		static const std::vector<vec2> &getDefaultUVs();
		static const std::vector<vec2> &getFlippedUVs();

	private:
		const Texture *texture;
		uint color;

		mutable std::vector<Vertex2D> vertices;
	};

}


#endif //X808_SPRITE_HPP
