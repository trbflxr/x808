//
// Created by FLXR on 7/2/2018.
//

#ifndef X808_LAYER2D_HPP
#define X808_LAYER2D_HPP


#include "layer.hpp"
#include "gfx/api/shader.hpp"
#include "gfx/renderer2d.hpp"
#include "gfx/camera/orthographiccamera.hpp"

namespace xe { namespace gfx {

	class XE_API Layer2D : public Layer {
	public:
		explicit Layer2D(const mat4 &projection, api::Shader *shader);
		~Layer2D() override;

		void render() override;

	protected:
		bool resize(uint width, uint height) override;

	protected:
		OrthographicCamera *camera;

		api::Shader *shader;
		Renderer2D *renderer;
		xe::GameObject *root;
	};

}}


#endif //X808_LAYER2D_HPP
