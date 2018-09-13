//
// Created by FLXR on 9/13/2018.
//

#ifndef X808_IRENDERABLE2D_HPP
#define X808_IRENDERABLE2D_HPP


#include <array>
#include <xe/common.hpp>
#include <xe/math/vec3.hpp>
#include <xe/gfx/texture.hpp>

namespace xe {

	class XE_API IRenderable2D {
	public:
		virtual ~IRenderable2D() = default;

		virtual const std::array<vec2, 4> &getUVs() const = 0;
		virtual const std::array<vec3, 4> &getVertices() const = 0;
		virtual const Texture *getTexture() const = 0;
		virtual uint getColor() const = 0;
		virtual bool isVisible() const = 0;
		virtual bool hasTransparency() const = 0;
		virtual const vec3 &getPosition() const = 0;
	};

}

#endif //X808_IRENDERABLE2D_HPP
