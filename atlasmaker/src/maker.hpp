//
// Created by FLXR on 2/25/2019.
//

#ifndef X808_MAKER_HPP
#define X808_MAKER_HPP


#include <unordered_map>
#include <xe/gfx/layer.hpp>
#include <xe/gfx/framebuffer.hpp>
#include <xe/gfx/2d/renderer2d.hpp>
#include <xe/gfx/2d/sprite.hpp>
#include <xe/utils/rectpack.hpp>
#include <xe/gfx/fx/quad.hpp>

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
		void create();

		FreeRectChoice chooseBestFit(std::vector<const Texture *> &textures, const vec2 &size) const;

	private:
		Camera *camera;
		Renderer2D *renderer;

		FrameBuffer *buffer;
		Texture *renderTexture;
		fx::Quad *quad;

		vec2 atlasSize;

		std::vector<const Texture *> textures;

		std::vector<Sprite *> sprites;
		std::vector<std::pair<string, rect>> pairs;
	};

}


#endif //X808_MAKER_HPP
