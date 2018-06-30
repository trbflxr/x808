//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_LAYER2D_HPP
#define X808_LAYER2D_HPP


#include "layer.hpp"
#include "common.hpp"
#include "gfx/renderer2d.hpp"
#include "math/mat4.hpp"

namespace xe { namespace gfx {

	class XE_API Layer2D : public Layer {
	public:
		explicit Layer2D(const mat4 &projectionMatrix);
		~Layer2D() override;

		virtual void init();
		virtual void init(Renderer2D& renderer);

		void render() override;
		virtual void render(Renderer2D& renderer) { }

		virtual Renderable2D *submit(Renderable2D *renderable);

	protected:
		bool resize(uint width, uint height) override;

	protected:
		Renderer2D *renderer;

		std::vector<Renderable2D *> submittedRenderables;
	};

}}


#endif //X808_LAYER2D_HPP
