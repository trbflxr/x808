//
// Created by FLXR on 7/2/2018.
//

#ifndef X808_LAYER2D_HPP
#define X808_LAYER2D_HPP


#include "layer.hpp"
#include "gfx/renderer2d.hpp"
#include "gfx/camera/orthographiccamera.hpp"

namespace xe { namespace gfx {

	class XE_API Layer2D : public Layer {
	public:
		explicit Layer2D(const mat4 &projection);
		~Layer2D() override;

	protected:
		bool resize(uint width, uint height) override;

	protected:
		OrthographicCamera *camera;

		Renderer2D *renderer;
	};

}}


#endif //X808_LAYER2D_HPP
