//
// Created by FLXR on 2/25/2019.
//

#include <xe/gfx/renderer.hpp>
#include <xe/ui/imgui/imgui.h>
#include <xe/ui/imgui/Imgui_file_dialog.hpp>
#include <xe/loaders/imageloader.hpp>
#include <xe/core/filesystem.hpp>
#include "maker.hpp"

namespace xe {

	const uint W = 2048;
	const uint H = 2048;

	Maker::Maker() :
			renderToTexture(false),
			showFileDialog(false) {

		atlasSize = vec2(W, H);
		screenSize = vec2(app.getWindowSize().x, app.getWindowSize().y);

		TextureParameters params;

		camera = new Camera(mat4::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1000.0f));
		renderCamera = new Camera(mat4::ortho(0.0f, atlasSize.x, 0.0f, atlasSize.y, -1.0f, 1000.0f));
		renderer = new Renderer2D(static_cast<uint>(atlasSize.x), static_cast<uint>(atlasSize.y), camera);

		renderTexture = new Texture("rt", W, H, 0, params, true);
		buffer = new FrameBuffer("rb");
		buffer->load({std::make_pair(Attachment::Color0, renderTexture)});

		atlas = new Sprite(renderTexture);

		Texture *t0 = new Texture("s0", "test1.png", params);
		Texture *t1 = new Texture("s1", "test2.png", params);
		Texture *t2 = new Texture("s2", "test3.png", params);
		Texture *t3 = new Texture("s3", "test4.png", params);
		Texture *sp0 = new Texture("sp0", "sp0.png", params);
		Texture *star = new Texture("star", "star.png", params);
		Texture *pepe = new Texture("pepe", "feelsconflictedman.jpg", params);

		textures.push_back(t0);
		textures.push_back(t1);
		textures.push_back(t2);
		textures.push_back(t3);
		textures.push_back(sp0);
		textures.push_back(star);
		textures.push_back(pepe);

		create();
	}

	Maker::~Maker() {
		delete camera;
		delete renderCamera;
		delete renderer;

		delete buffer;
		delete renderTexture;
		delete atlas;

		for (auto &&s : sprites) {
			delete s;
		}

		for (auto &&t : textures) {
			delete t;
		}
	}

	void Maker::create() {
		RectPack pack(static_cast<int32>(atlasSize.x), static_cast<int32>(atlasSize.y), false);

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

		renderToTexture = true;
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
			pack.init(static_cast<int32>(size.x), static_cast<int32>(size.y));

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

	void Maker::store() {
		if (!renderToTexture) return;

		renderToTexture = false;

		renderer->setCamera(renderCamera);
		renderer->setWidth(static_cast<uint>(atlasSize.x));
		renderer->setHeight(static_cast<uint>(atlasSize.y));

		buffer->bindDraw(Attachment::Color0);
		Renderer::setViewport(0, 0, renderer->getWidth(), renderer->getHeight());


		static constexpr float color[4] = {0, 0, 0, 0};
		Renderer::clearBufferF(Attachment::Color0, color);

		renderer->begin();

		for (auto &&s : sprites) {
			renderer->submit(s);
		}

		renderer->end();
		renderer->flush();

		buffer->unbind();

		renderer->setCamera(camera);
		renderer->setWidth(static_cast<uint>(screenSize.x));
		renderer->setHeight(static_cast<uint>(screenSize.y));
	}

	void Maker::render() {
		store();

		renderer->begin();

		renderer->submit(atlas);

		renderer->end();
		renderer->flush();
	}

	void Maker::renderImGui() {
		ImGui::Begin("UI");

		ImGui::Text("info");
		ImGui::Text("fps: %i", app.getFPS());
		ImGui::Text("frame time: %.3f", app.getFrameTime());
		ImGui::Text("draw calls: %i", Renderer::getDC());
		ImGui::Separator();
		ImGui::Dummy({10.0f, 0.0f});

		if (ImGui::Button("save")) {
			byte *data = renderTexture->getData2D();
			ImageLoader::packAtlas("test.atlas", atlasSize.x, atlasSize.y, pairs, data, true);
			delete[] data;
		}

		if (ImGui::Button("Open File Dialog")) {
			showFileDialog = true;
		}


		if (showFileDialog) {
			if (ImGuiFileDialog::open("Select files")) {

				auto files = ImGuiFileDialog::getFiles();
				ImGuiFileDialog::reset();

				for (const auto &f : files) {
					XE_CORE_TRACE(f.path);
				}

				showFileDialog = false;
			}
		}

		ImGui::End();
	}

	void Maker::update(float delta) {
		///update camera
		vec3 camPos = camera->transform.getPosition();

		if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
			camPos.x += 1000 * delta;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
			camPos.x -= 1000 * delta;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
			camPos.y += 1000 * delta;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
			camPos.y -= 1000 * delta;
		}
		camera->transform.setPosition(camPos);

		camera->update();
	}

	void Maker::input(Event &event) {

	}

	void Maker::resize(int32 width, int32 height) {
		screenSize = vec2(width, height);
		camera->setProjection(mat4::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1000.0f));
		renderer->setWidth(width);
		renderer->setHeight(height);
	}

}