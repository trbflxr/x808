//
// Created by FLXR on 9/7/2018.
//

#include <xe/ui/imgui/imgui_impl_xe.hpp>
#include <xe/utils/logger.hpp>
#include <xe/gfx/color.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/utils/random.hpp>
#include <xe/gfx/2d/rectangleshape.hpp>
#include "uilayer.hpp"

namespace xe {

	static uint w = 512;
	static uint h = 512;

	UILayer::UILayer() {
		TextureParameters params;
		renderTexture = new Texture("renderTexture", w, h, 0, params, true);

		renderWindow = new FrameBuffer("renderWindow");
		renderWindow->load({std::make_pair(Attachment::Color0, renderTexture)});

		quad = new Quad(w, h);

		//test
		camera = new Camera(mat4::ortho(0.0f, w, 0.0f, h, -1.0f, 1000.0f));
		renderer = new Renderer2D(w, h, camera);


		Texture *tex = new Texture("a", "test1.png", params);

		for (int32 x = 0; x < 512; x += 15) {
			for (int32 y = 0; y < 512; y += 15) {
				RectangleShape *s = new RectangleShape({10.0f, 10.0f});
				s->setTexture(tex);
				s->transformation(vec2(x, y));

				renderables.push_back(s);
			}
		}
	}

	UILayer::~UILayer() {
		delete renderTexture;
		delete renderWindow;

		//test
		delete camera;
		delete renderer;

		for (const auto &r : renderables) {
			delete r;
		}
	}

	void UILayer::render() {
		//render to buffer
		renderWindow->bindDraw(Attachment::Color0);
		Renderer::setViewport(0, 0, w, h);

		static constexpr float color[4] = {0, 1, 0, 1};
		Renderer::clearBufferF(Attachment::Color0, color);


		renderer->begin();

		for (const auto &r : renderables) {
			((RectangleShape *) r)->rotate(0.5f);
			renderer->submit(r);
		}

		renderer->end();
		renderer->flush();


		renderWindow->unbind();
	}

	void UILayer::renderImGui() {
		Renderer::setClearColor(color::Black);

		static bool open = true;
		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
		bool opt_fullscreen = opt_fullscreen_persistant;


		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen) {
			const ImGuiViewport *viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
			                ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace) {
			window_flags |= ImGuiWindowFlags_NoBackground;
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen) {
			ImGui::PopStyleVar(2);
		}

		// Dockspace
		ImGuiIO &io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);

			ImGui::ShowDemoWindow(&open);


			ImGui::Begin("Render window");
			ImGui::Text("Preview");
			ImGui::Image(reinterpret_cast<void *>(renderTexture->getHandle()), {512, 512}, {1, 1}, {0, 0});
			ImGui::End();
		}

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("Docking")) {
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Flag: NoSplit", "", (opt_flags & ImGuiDockNodeFlags_NoSplit) != 0))
					opt_flags ^= ImGuiDockNodeFlags_NoSplit;
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "",
				                    (opt_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))
					opt_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
				if (ImGui::MenuItem("Flag: PassthruDockspace", "",
				                    (opt_flags & ImGuiDockNodeFlags_PassthruDockspace) != 0))
					opt_flags ^= ImGuiDockNodeFlags_PassthruDockspace;

				ImGui::Separator();
				if (ImGui::MenuItem("Close DockSpace", nullptr, false)) {
					open = false;
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();
	}

	void UILayer::update(float delta) { }
	
	void UILayer::fixedUpdate(float delta){ }

	void UILayer::input(xe::Event &event) { }

}
