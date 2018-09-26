//
// Created by FLXR on 9/7/2018.
//

#ifndef X808_UILAYER_HPP
#define X808_UILAYER_HPP


#include <xe/gfx/layer.hpp>
#include <xe/gfx/framebuffer.hpp>

class UILayer : public xe::Layer {
public:
	explicit UILayer();
	~UILayer() override;

	void render() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	void initImGui();

private:
	void *dockContext;

	//framebuffer
	xe::FrameBuffer *renderWindow;
	xe::Texture *renderTexture;
};


#endif //X808_UILAYER_HPP
