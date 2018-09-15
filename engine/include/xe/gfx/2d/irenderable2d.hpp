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
		explicit IRenderable2D(bool transparency, bool visible) :
				transparency(transparency),
				visible(visible) { }

		virtual ~IRenderable2D() = default;

		virtual uint getVerticesSize() const = 0;
		virtual const std::vector<Vertex2D> &getVertices() const = 0;
		virtual const Texture *getTexture() const = 0;
		virtual uint getColor() const = 0;

		inline bool isVisible() const { return visible; }
		inline void setVisible(bool visible) { IRenderable2D::visible = visible; }

		inline bool hasTransparency() const { return transparency; }

	protected:
		bool transparency;
		bool visible;
	};

}

#endif //X808_IRENDERABLE2D_HPP
