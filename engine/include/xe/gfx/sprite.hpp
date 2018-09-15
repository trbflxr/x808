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

		~Sprite() override;

		inline uint getVerticesSize() const override { return 4; }
		const Vertex2D *getVertices() const override;

		inline uint getIndicesSize() const override { return 6; }
		inline const uint *getIndices() const override { return indices; }

		static const std::vector<vec2> &getDefaultUVs();
		static const std::vector<vec2> &getFlippedUVs();

	private:
		mutable Vertex2D *vertices;
		uint *indices;
	};

}


#endif //X808_SPRITE_HPP
