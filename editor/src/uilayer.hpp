//
// Created by FLXR on 9/7/2018.
//

#ifndef X808_UILAYER_HPP
#define X808_UILAYER_HPP


#include <xe/gfx/layer.hpp>

class UILayer : public xe::Layer {
public:
	explicit UILayer();
	~UILayer() override;

	void render() override;

	void update(float delta) override;

	void input(xe::Event &event) override;

private:
	void *dockContext;
};


#endif //X808_UILAYER_HPP
