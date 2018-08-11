//
// Created by FLXR on 8/7/2018.
//

#ifndef X808_QUAD_HPP
#define X808_QUAD_HPP


#include "common.hpp"
#include "rendereffect.hpp"
#include "gfx/api/vertexarray.hpp"
#include "gfx/api/indexbuffer.hpp"
#include "gfx/api/enums.hpp"

namespace xe { namespace fx {

	class XE_API Quad : public RenderEffect {
	public:
		explicit Quad(uint width, uint height);
		~Quad();

		void render() const;
		void render(BlendFunction src, BlendFunction dest, BlendEquation eq = BlendEquation::Add) const;

	private:
		api::VertexArray *vao;
		api::IndexBuffer *ibo;
		uint indicesCount;
	};

}}


#endif //X808_QUAD_HPP
