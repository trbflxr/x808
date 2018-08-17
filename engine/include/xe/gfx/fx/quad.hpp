//
// Created by FLXR on 8/7/2018.
//

#ifndef X808_QUAD_HPP
#define X808_QUAD_HPP


#include <xe/common.hpp>
#include <xe/gfx/fx/rendereffect.hpp>
#include <xe/gfx/vertexarray.hpp>
#include <xe/gfx/indexbuffer.hpp>
#include <xe/gfx/enums.hpp>

namespace xe { namespace fx {

	class XE_API Quad : public RenderEffect {
	public:
		explicit Quad(uint width, uint height);
		~Quad();

		void render() const;
		void render(BlendFunction src, BlendFunction dest, BlendEquation eq = BlendEquation::Add) const;

	private:
		VertexArray *vao;
		IndexBuffer *ibo;
		uint indicesCount;
	};

}}


#endif //X808_QUAD_HPP
