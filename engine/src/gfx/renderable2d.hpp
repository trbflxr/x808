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
#include "core/gameobject.hpp"

namespace xe { namespace gfx {

	class Renderer2D;

	struct VertexData {
		vec3 vertex;
		vec2 uv;
		float tid;
		uint color;
	};

#define RENDERER_VERTEX_SIZE sizeof(VertexData)

	class XE_API Renderable2D : public GameObject {
	private:
		friend class Renderer2D;

	public:
		explicit Renderable2D(const vec2 &size, uint color);
		virtual ~Renderable2D() = default;

		virtual void submit(Renderer2D *renderer);

		inline const api::Texture *getTexture() const { return texture; }
		inline const std::vector<vec2> &getUVs() const { return UVs; }

		inline uint getColor() const { return color; }
		inline void setColor(uint color) { Renderable2D::color = color; }

		inline const vec2 &getSize() const { return size; }
		inline void setSize(const vec2 &size) { Renderable2D::size = size; }

		inline bool isVisible() const { return visible; }
		inline void setVisible(bool visible) { Renderable2D::visible = visible; }

		static const std::vector<vec2> &getDefaultUVs();

	protected:
		Renderable2D();

	protected:
		uint color;
		vec2 size;

		std::vector<vec2> UVs;
		const api::Texture *texture;

		bool visible;
	};

}}


#endif //X808_RENDERABLE2D_HPP
