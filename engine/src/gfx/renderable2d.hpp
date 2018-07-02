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
	private:
		friend class Renderer2D;

	public:
		virtual ~Renderable2D() = default;

		virtual void submit(Renderer2D *renderer) const;

		inline void move(const vec2 &direction) { bounds.move(direction); }
		inline void rotate(float deg) { bounds.rotate(deg); }

		inline const vec2 &getSize() const { return bounds.getSize(); }
		inline void setSize(const vec2 &size) { bounds.setSize(size); }

		inline const vec2 &getPosition() const { return bounds.getPosition(); }
		inline void setPosition(const vec2 &position) { bounds.setPosition(position); }

		inline float getRotation() const { return bounds.getRotation(); }
		inline void setRotation(float deg) { bounds.setRotation(deg); }

		inline uint getColor() const { return color; }
		inline void setColor(uint color) { Renderable2D::color = color; }

		inline bool isVisible() const { return visible; }
		inline void setVisible(bool visible) { Renderable2D::visible = visible; }

		inline const api::Texture *getTexture() const { return texture; }
		inline const std::vector<vec2> &getUVs() const { return UVs; }


		static const std::vector<vec2> &getDefaultUVs();

	protected:
		explicit Renderable2D(const vec2 &position, const vec2 &size, float rotation, uint color = color::WHITE);
		Renderable2D();

	protected:
		aobb bounds;
		uint color;

		std::vector<vec2> UVs;
		const api::Texture *texture;

		bool visible;
	};

}}


#endif //X808_RENDERABLE2D_HPP
