//
// Created by FLXR on 2/25/2019.
//

#include <new>
#include <xe/gfx/renderer.hpp>
#include <xe/ui/imgui/imgui.h>
#include <xe/ui/imgui/Imgui_file_dialog.hpp>
#include <xe/loaders/imageloader.hpp>
#include <xe/core/filesystem.hpp>
#include "maker.hpp"

namespace xe {

	Maker::Maker() :
			params(TextureTarget::Tex2D, PixelInternalFormat::Rgba, PixelFormat::Rgba, PixelType::UnsignedByte),
			renderToTexture(false),
			openFileDialog(false),
			saveFileDialog(false),
			mouseGrabbed(false),
			allowDrag(false),
			uiFocused(false),
			updateTextureList(true),
			renderTexture(nullptr),
			atlas(nullptr),
			atlasSize(0.0f),
			scale(1.0f) {

		screenSize = vec2(app.getWindowSize().x, app.getWindowSize().y);

		camera = new Camera(mat4::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f));
		renderCamera = new Camera(mat4::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f));
		renderer = new Renderer2D(static_cast<uint>(screenSize.x), static_cast<uint>(screenSize.y), camera);

		renderTexture = new Texture("rt", 1, 1, 0, params);

		buffer = new FrameBuffer("rb");
		buffer->load({std::make_pair(Attachment::Color0, renderTexture)});

		atlas = new Sprite(renderTexture);
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

	void Maker::create(int32 size) {
		atlasSize = vec2(size, size);

		renderCamera->setProjection(mat4::ortho(0.0f, atlasSize.x, 0.0f, atlasSize.y, -1.0f, 1.0f));


		renderTexture->~Texture();
		renderTexture = new(renderTexture) Texture("rt", static_cast<uint>(atlasSize.x),
		                                           static_cast<uint>(atlasSize.y), 0, params, true);

		atlas->setTexture(renderTexture);
		buffer->load({std::make_pair(Attachment::Color0, renderTexture)});

		pack();
	}

	void Maker::pack() {
		for (const auto &s : sprites) {
			delete s;
		}
		sprites.clear();

		pairs.clear();

		const FreeRectChoice best = chooseBestFit();
		RectPack pack(atlasSize.x, atlasSize.y, false);

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

	FreeRectChoice Maker::chooseBestFit() const {
		static std::vector<FreeRectChoice> heu = {FreeRectChoice::BestShortSideFit,
		                                          FreeRectChoice::BestLongSideFit,
		                                          FreeRectChoice::BestAreaFit,
		                                          FreeRectChoice::BottomLeftRule,
		                                          FreeRectChoice::ContactPointRule};
		RectPack pack;

		FreeRectChoice r = heu[0];
		float max = 0.0f;

		for (const auto &h : heu) {
			pack.init(static_cast<int32>(atlasSize.x), static_cast<int32>(atlasSize.y));

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

		if (atlas) {
			renderer->submit(atlas);
		}

		renderer->end();
		renderer->flush();
	}

	void Maker::renderImGui() {
		ImGui::Begin("Atlas maker");

		ImGui::Text("fps: %i", app.getFPS());
		ImGui::Text("frame time: %.3f", app.getFrameTime());
		ImGui::Text("draw calls: %i", Renderer::getDC());
		ImGui::Text("scale: %.2f", scale);
		ImGui::Separator();
		ImGui::Dummy({10.0f, 0.0f});

		renderSizeCombo();

		if (ImGui::Button("Open File Dialog") && !saveFileDialog) {
			openFileDialog = true;
		}

		if (ImGui::Button("Save File Dialog") && !openFileDialog) {
			saveFileDialog = true;
		}

		if (openFileDialog) {
			if (ImGuiFileDialog::open("Select files")) {

				auto files = ImGuiFileDialog::getFiles();
				ImGuiFileDialog::reset();

				updateTextureList = true;

				for (const auto &f : files) {
					bool found = false;
					for (const auto &t : textures) {
						if (t->getFilePath() == f.path) {
							found = true;
							break;
						}
					}

					if (!found) {
						textures.push_back(new Texture(f.name, f.path, params));
					}
				}

				openFileDialog = false;
			}
		}

		if (saveFileDialog) {
			if (ImGuiFileDialog::save("Save file")) {
				string path = ImGuiFileDialog::getSavePath();
				ImGuiFileDialog::reset();

				if (!path.empty()) {
					if (!sprites.empty()) {
						byte *data = renderTexture->getData2D();
						ImageLoader::packAtlas(path, atlasSize.x, atlasSize.y, pairs, data, true);
						delete[] data;
					}
				}

				saveFileDialog = false;
			}
		}

		renderTextureList();

		ImGui::End();

		uiFocused = ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
	}

	void Maker::renderSizeCombo() {
		static const uint n = 4;
		static const char *sizes[n] = {"512", "1024", "2048", "4096"};
		static const char *selectedSize = "512";

		ImGui::PushItemWidth(70);
		if (ImGui::BeginCombo("##sizeCombo", selectedSize)) {
			for (auto &&s : sizes) {
				bool selected = selectedSize == s;
				if (ImGui::Selectable(s, selected)) {
					selectedSize = s;
				}
				if (selected) {
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		ImGui::SameLine();
		if (ImGui::Button("Create")) {
			if (!textures.empty()) {
				create(atoi(selectedSize));
			}
		}
	}

	void Maker::renderTextureList() {
		ImGui::Separator();

		static std::vector<string> tl;

		if (updateTextureList) {
			updateTextureList = false;
			tl.clear();

			for (const auto &t : textures) {
				tl.emplace_back(t->getName());
			}
		}

		static int32 selected = -1;
		ImGui::PushItemWidth(ImGui::GetWindowWidth());
		ImGui::ListBoxHeader("", static_cast<int32>(tl.size()));
		for (int32 i = 0; i < static_cast<int32>(tl.size()); ++i) {
			if (ImGui::Selectable(tl[i].c_str(), selected == i)) {
				selected = i;
			}
		}
		ImGui::ListBoxFooter();

		if (selected != -1 && ImGui::IsKeyDown(Keyboard::Delete)) {
			tl.erase(tl.begin() + selected);
			textures.erase(textures.begin() + selected);
			selected = -1;
			pack();
		}
	}

	void Maker::input(Event &event) {
		static vec2 lastMousePos = Mouse::getPosition(window);

		if (event.type == Event::MouseButtonPressed) {
			if (event.mouseButton.button == Mouse::Button::Left) {
				lastMousePos = Mouse::getPosition(window);
				mouseGrabbed = true;
				event.handled = true;
				return;
			}
		}
		if (event.type == Event::MouseButtonReleased) {
			if (event.mouseButton.button == Mouse::Button::Left) {
				mouseGrabbed = false;
				event.handled = true;
				return;
			}
		}

		if (event.type == Event::MouseLeft) {
			allowDrag = false;
			event.handled = true;
			return;
		}

		if (event.type == Event::MouseEntered) {
			allowDrag = true;
			event.handled = true;
			return;
		}

		if (event.type == Event::MouseMoved) {
			if (mouseGrabbed && allowDrag && !uiFocused) {
				const vec2 newPos = vec2(event.mouseMove.x, event.mouseMove.y);
				const vec2 change = lastMousePos - newPos;

				camera->transform.move(vec3(change));

				camera->update();

				lastMousePos = newPos;

				event.handled = true;
				return;
			}
		}

		if (event.type == Event::MouseWheelMoved && !uiFocused) {
			static constexpr float speed = 0.1f;
			scale += event.mouseWheel.delta * speed;
			if (scale < 0.1f) {
				scale = 0.1f;
			}

			atlas->setScale({scale, scale});
			event.handled = true;
			return;
		}
	}

	void Maker::resize(int32 width, int32 height) {
		screenSize = vec2(width, height);
		camera->setProjection(mat4::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f));
		renderer->setWidth(width);
		renderer->setHeight(height);
	}

}