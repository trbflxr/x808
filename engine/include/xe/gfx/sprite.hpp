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
		explicit Sprite(const Texture *texture, float layer = 0.0f);
		~Sprite() override;

		inline const Texture *getTexture() const override { return texture; }
		void setTexture(const Texture *texture);

		inline const rect &getTextureRect() const { return textureRect; }
		void setTextureRect(const rect &rect);

		inline uint getPointCount() const override { return 4; }
		inline const Vertex2D *getVertices() const override { return vertices; }

		inline uint getIndicesCount() const override { return 6; }
		inline const uint *getIndices() const override { return indices; }

		void setLayer(float layer) override;

		inline const mat4 &getTransformation() const override { return toMatrix(); }

	private:
		void update();

	private:
		Vertex2D *vertices;
		uint *indices;

		rect textureRect;
		const Texture *texture;
	};

}


#endif //X808_SPRITE_HPP
