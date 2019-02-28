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

namespace xe {

	class Maker : public Layer {
	public:
		explicit Maker();
		~Maker() override;

		void render() override;
		void renderImGui() override;

		void input(Event &event) override;

	protected:
		void resize(int32 width, int32 height) override;

	private:
		void create(int32 size);

		void pack();

		void store();

		void renderSizeCombo();
		void renderTextureList();

		FreeRectChoice chooseBestFit() const;

	private:
		const TextureParameters params;

		bool renderToTexture;
		bool openFileDialog;
		bool saveFileDialog;
		bool mouseGrabbed;
		bool allowDrag;
		bool uiFocused;
		bool updateTextureList;

		Camera *camera;
		Camera *renderCamera;
		Renderer2D *renderer;

		FrameBuffer *buffer;
		Texture *renderTexture;

		Sprite *atlas;

		vec2 atlasSize;
		vec2 screenSize;
		float scale;

		std::vector<const Texture *> textures;

		std::vector<Sprite *> sprites;
		std::vector<std::pair<string, rect>> pairs;
	};

}


#endif //X808_MAKER_HPP
