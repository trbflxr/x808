//
// Created by FLXR on 7/2/2018.
//

#ifndef X808_LAYER2D_HPP
#define X808_LAYER2D_HPP


#include <xe/gfx/renderer2d.hpp>
#include <xe/gfx/layers/layer.hpp>

namespace xe {

	class XE_API Layer2D : public Layer {
	public:
		explicit Layer2D();
		virtual ~Layer2D();

	protected:
		bool resize(uint width, uint height) override;

	protected:
		Renderer2D *renderer;
	};

}


#endif //X808_LAYER2D_HPP
