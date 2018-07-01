//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_LAYER2D_HPP
#define X808_LAYER2D_HPP


#include "layer.hpp"
#include "common.hpp"
#include "gfx/renderer2d.hpp"
#include "gfx/scene2d.hpp"
#include "gfx/sprite.hpp"
#include "math/mat4.hpp"

namespace xe { namespace gfx {

	class XE_API Layer2D : public Layer {
	public:
		explicit Layer2D(const mat4 &projectionMatrix);
		explicit Layer2D(Scene2D *scene);
		~Layer2D() override;

		void init() override;
		virtual void init(Renderer2D& renderer) { }

		void render() override;
		virtual void render(Renderer2D& renderer) { }

		virtual Sprite *add(Sprite *sprite);
		virtual Renderable2D *submit(Renderable2D *renderable);

		inline Scene2D *getScene() { return scene; }

	protected:
		bool resize(uint width, uint height) override;

	protected:
		Renderer2D *renderer;

		Scene2D *scene;
		std::vector<Renderable2D *> submittedRenderables;
	};

}}


#endif //X808_LAYER2D_HPP
