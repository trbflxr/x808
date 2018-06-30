//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_RENDERABLE2D_HPP
#define X808_RENDERABLE2D_HPP


#include <vector>
#include "common.hpp"
#include "color.hpp"
#include "math/math.hpp"
#include "gfx/api/texture.hpp"

namespace xe { namespace gfx {

	class Renderer2D;

	struct VertexData {
		vec3 vertex;
		vec2 uv;
		float tid;
		uint color;
	};

#define RENDERER_VERTEX_SIZE sizeof(VertexData)

	class XE_API Renderable2D {
	public:
		explicit Renderable2D(const vec2 &position, const vec2 &size, uint color);
		virtual ~Renderable2D();

		virtual void submit(Renderer2D *renderer) const;

		inline const vec2 &getPosition() const { return bounds.position; }
		inline const vec2 &getSize() const { return bounds.size; }

		inline const rect &getBounds() const { return bounds; }
		inline rect &getBounds() { return bounds; }

		inline aabb getBoundingBox() const { return aabb(bounds); }
		inline uint getColor() const { return color; }

		inline api::Texture *getTexture() const { return texture; }
		inline const std::vector<vec2> &getUVs() const { return UVs; }

		inline bool isVisible() const { return visible; }

		inline void setPosition(const vec2 &position) { bounds.position = position; }
		inline void setSize(const vec2 &size) { bounds.size = size; }
		inline void setColor(uint color) { Renderable2D::color = color; }

		inline void setVisible(bool visible) { Renderable2D::visible = visible; }

		static const std::vector<vec2> &getDefaultUVs();

	protected:
		Renderable2D();

	protected:
		rect bounds;
		uint color;

		std::vector<vec2> UVs;
		api::Texture *texture;

		bool visible;
	};

}}


#endif //X808_RENDERABLE2D_HPP
