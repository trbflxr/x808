//
// Created by FLXR on 9/6/2018.
//

#ifndef X808_RENDERER2D_HPP
#define X808_RENDERER2D_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/gfx/2d/irenderer2d.hpp>
#include <xe/gfx/2d/irenderable2d.hpp>

namespace xe {

	class XE_API Renderer2D : public IRenderer2D {
	public:
		explicit Renderer2D(uint width, uint height, Camera *camera);

		void submit(const IRenderable2D *target);

		void begin() override;
		void end() override;
		void flush() override;

		void render(const std::vector<const IRenderable2D *> &targets);

	private:
		void submitInternal(const IRenderable2D *target);

	private:
		std::vector<const IRenderable2D *> targets;
		std::vector<const IRenderable2D *> transparentTargets;
	};
}


#endif //X808_RENDERER2D_HPP
