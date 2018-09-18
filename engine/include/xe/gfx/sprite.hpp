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

	class XE_API Sprite : public IRenderable2D, public ITransformable2D {
	public:
		explicit Sprite(const Texture *texture, bool flipUVs = false);
		~Sprite() override;

		inline uint getPointCount() const override { return 4; }
		const Vertex2D *getVertices() const override { return vertices; }
		inline const uint *getIndices() const override { return indices; }

		inline float getZ() const override { return getPosition().z; }

		static const std::vector<vec2> &getDefaultUVs();
		static const std::vector<vec2> &getFlippedUVs();

	private:
		void updateVertices();

	private:
		mutable Vertex2D *vertices;
		uint *indices;
	};

}


#endif //X808_SPRITE_HPP
