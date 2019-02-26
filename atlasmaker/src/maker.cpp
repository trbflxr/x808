//
// Created by FLXR on 2/25/2019.
//

#include <xe/gfx/renderer.hpp>
#include <xe/ui/imgui/imgui.h>
#include <xetools/spak.hpp>
#include "maker.hpp"

#include <GL/glew.h> //fixme:

namespace xe {

	const float W = 2048;
	const float H = 2048;

	Maker::Maker() {
		const float width = app.getWindowSize().x;
		const float height = app.getWindowSize().y;

		TextureParameters params;

		camera = new Camera(mat4::ortho(0.0f, W, 0.0f, H, -1.0f, 1000.0f));
		renderer = new Renderer2D(W, H, camera);

		renderTexture = new Texture("rt", W, H, 0, params, true);
		buffer = new FrameBuffer("rb");
		buffer->load({std::make_pair(Attachment::Color0, renderTexture)});

		quad = new fx::Quad(W, H);

		atlasSize = vec2(W, H);

		Texture *t0 = new Texture("s0", "test1.png", params);
		Texture *t1 = new Texture("s1", "test2.png", params);
		Texture *t2 = new Texture("s2", "test3.png", params);
		Texture *t3 = new Texture("s3", "test4.png", params);
		Texture *sp0 = new Texture("sp0", "sp0.png", params);
		Texture *sp1 = new Texture("sp1", "sp1.png", params);
		Texture *star = new Texture("star", "star.png", params);
		Texture *wide = new Texture("wide", "wide.png", params);
		Texture *pepe = new Texture("pepe", "feelsconflictedman.jpg", params);
		Texture *g = new Texture("grass", "grass.png", params);

		textures.push_back(t0);
		textures.push_back(t1);
		textures.push_back(t2);
		textures.push_back(t3);
		textures.push_back(sp0);
		textures.push_back(sp1);
		textures.push_back(wide);
		textures.push_back(star);
		textures.push_back(pepe);
		textures.push_back(g);

		create();
	}

	Maker::~Maker() {
		delete camera;
		delete renderer;

		delete buffer;
		delete renderTexture;

		for (auto &&s : sprites) {
			delete s;
		}

		for (auto &&t : textures) {
			delete t;
		}
	}

	void Maker::create() {
		RectPack pack(atlasSize.x, atlasSize.y, false);

		const FreeRectChoice best = chooseBestFit(textures, atlasSize);

		for (const auto &t : textures) {
			rect packed = pack.insert(t->getWidth(), t->getHeight(), best);

			if (packed.height < 0.0f) {
				XE_CORE_ERROR("Pack is full");
			}

			Sprite *s = new Sprite(t);
			s->setPosition({packed.x, packed.y});
			sprites.push_back(s);

			rect r(s->getTextureRect().position + vec2(packed.x, packed.y), s->getTextureRect().size);
			pairs.emplace_back(s->getTexture()->getName(), r);
		}
	}

	FreeRectChoice Maker::chooseBestFit(std::vector<const Texture *> &textures, const vec2 &size) const {
		static std::vector<FreeRectChoice> heu = {FreeRectChoice::BestShortSideFit,
		                                          FreeRectChoice::BestLongSideFit,
		                                          FreeRectChoice::BestAreaFit,
		                                          FreeRectChoice::BottomLeftRule,
		                                          FreeRectChoice::ContactPointRule};
		RectPack pack;

		FreeRectChoice r = heu[0];
		float max = 0.0f;

		for (const auto &h : heu) {
			pack.init(size.x, size.y);

			for (const auto &s : textures) {
				pack.insert(s->getWidth(), s->getHeight(), h);
			}

			if (pack.occupancy() > max) {
				max = pack.occupancy();
				r = h;
			}
		}

		return r;
	}

	void Maker::render() {
		buffer->bindDraw(Attachment::Color0);
		Renderer::setViewport(0, 0, W, H);


		static constexpr float color[4] = {0, 0, 0, 0};
		Renderer::clearBufferF(Attachment::Color0, color);

		renderer->begin();

		for (auto &&s : sprites) {
			renderer->submit(s);
		}

		renderer->end();
		renderer->flush();

		buffer->unbind();


		quad->renderTexture(renderTexture);
	}

	void Maker::renderImGui() {
		ImGui::Begin("Save");


		if (ImGui::Button("save")) {
			byte *data = renderTexture->getData2D();

			spak::packAtlas("test.png", W, H, pairs, data, true);

			delete[] data;
		}

		ImGui::End();
	}

	void Maker::update(float delta) {

	}

	void Maker::input(Event &event) {

	}
}