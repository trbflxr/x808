//
// Created by FLXR on 9/13/2018.
//

#ifndef X808_IRENDERABLE2D_HPP
#define X808_IRENDERABLE2D_HPP


#include <vector>
#include <xe/common.hpp>
#include <xe/math/vec3.hpp>
#include <xe/math/vec2.hpp>
#include <xe/gfx/texture.hpp>

namespace xe {

	struct Vertex2D {
		vec3 pos;
		vec2 uv;
	};

	class XE_API IRenderable2D {
	public:
		explicit IRenderable2D(const Texture *texture, uint color, bool transparency, bool visible) :
				texture(texture),
				color(color),
				transparency(transparency),
				visible(visible) { }

		virtual ~IRenderable2D() = default;

		virtual uint getVerticesSize() const = 0;
		virtual const Vertex2D *getVertices() const = 0;

		virtual uint getIndicesSize() const = 0;
		virtual const uint *getIndices() const = 0;

		inline const Texture *getTexture() const { return texture; }
		inline void setTexture(const Texture *texture) { IRenderable2D::texture = texture; }

		uint getColor() const { return color; }
		void setColor(uint color) { IRenderable2D::color = color; }

		inline bool isVisible() const { return visible; }
		inline void setVisible(bool visible) { IRenderable2D::visible = visible; }

		inline bool hasTransparency() const { return transparency; }

	protected:
		const Texture *texture;
		uint color;

		bool transparency;
		bool visible;
	};

}

#endif //X808_IRENDERABLE2D_HPP
