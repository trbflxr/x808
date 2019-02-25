//
// Created by FLXR on 2/25/2019.
//

#ifndef X808_MAKER_HPP
#define X808_MAKER_HPP


#include <unordered_map>
#include <xe/gfx/layer.hpp>
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/sprite.hpp>

namespace xe {

	class Maker : public Layer {
	public:
		explicit Maker();
		~Maker() override;

		void render() override;
		void renderImGui() override;

		void update(float delta) override;

		void input(Event &event) override;

	private:
		xe::Camera *camera;
		xe::Renderer2D *renderer;

		xe::Texture *texture;

		std::unordered_map<string, xe::Sprite *> sprites;
	};

}


#endif //X808_MAKER_HPP
