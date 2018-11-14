//
// Created by FLXR on 9/7/2018.
//

#ifndef X808_UILAYER_HPP
#define X808_UILAYER_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/batchrenderer2d.hpp>

namespace xe {

	class UILayer : public Layer {
	public:
		explicit UILayer();
		~UILayer() override;

		void render() override;

		void update(float delta) override;

		void input(Event &event) override;

	private:
		void initImGui();

		void renderPreview();

	private:
		//framebuffer
		FrameBuffer *renderWindow;
		Texture *renderTexture;

		//test
		Camera *camera;
		BatchRenderer2D *renderer;

		std::vector<IRenderable2D *> renderables;
	};

}


#endif //X808_UILAYER_HPP
