//
// Created by FLXR on 9/7/2018.
//

#include <imgui_impl_xe_gl.hpp>
#include <xe/utils/log.hpp>
#include <xe/gfx/color.hpp>
#include <xe/gfx/renderer.hpp>
#include "uilayer.hpp"

using namespace xe;

UILayer::UILayer() {
	initImGui();

	TextureParameters params;
//	renderTexture = new Texture("a", L"assets/textures/test1.png", params);
	renderTexture = new Texture("renderTexture", 512, 512, 0, params);

	renderWindow = new FrameBuffer("renderWindow");
	renderWindow->load({std::make_pair(Attachment::Color0, renderTexture)});
}

UILayer::~UILayer() {
	ImGui::SaveDock("dock.ini");

	ImGui::xe::shutdown();

	ImGui::DestroyDockContext((ImGui::DockContext *) dockContext);

	delete renderTexture;
	delete renderWindow;
}

void UILayer::initImGui() {
	ImGui::xe::init(window);

	ImGui::StyleColorsDark();

	dockContext = ImGui::CreateDockContext();
	ImGui::SetCurrentDockContext((ImGui::DockContext *) dockContext);

	ImGui::LoadDock("dock.ini");
}

void UILayer::render() {
	//ImGui::ShowDemoWindow(&show_demo_window);

	renderWindow->bindDraw(Attachment::Color0);
	Renderer::setViewport(0, 0, 512, 512);
	Renderer::setClearColor(color::GREEN);
	Renderer::clear(RendererBufferColor);
	
//	glColor3f(1, 0, 1);
//	glBegin(GL_TRIANGLES);
//	glVertex2f(0, 0);
//	glVertex2f(1, 0);
//	glVertex2f(1, 1);
//	glEnd();

	renderWindow->unbind();


	// Fullscreen (without visual artifacts):
	ImGui::SetNextWindowPos({0, 0});
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

	const ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove |
	                               ImGuiWindowFlags_NoBringToFrontOnFocus |
	                               ImGuiWindowFlags_NoResize |
	                               ImGuiWindowFlags_NoScrollbar |
	                               ImGuiWindowFlags_NoSavedSettings |
	                               ImGuiWindowFlags_NoTitleBar;

	const float oldWindowRounding = ImGui::GetStyle().WindowRounding;

	ImGui::GetStyle().WindowRounding = 0;

	const bool visible = ImGui::Begin("imguidock window", nullptr, {0, 0}, 1.0f, flags);

	ImGui::GetStyle().WindowRounding = oldWindowRounding;

	if (visible) {
		ImGui::BeginDockspace();
		static char tmp[128];
		for (int i = 0; i < 10; i++) {
			sprintf(tmp, "Dock %d", i);

			if (i == 8) {
				ImGui::SetNextDock(ImGuiDockSlot_Right);// optional

				if (ImGui::BeginDock(tmp)) {
					ImGui::Text("Render window");

					ImGui::Image((void *) renderTexture->getHandle(), {512, 512});
				}
				ImGui::EndDock();

				continue;
			}

			if (i == 9) {
				ImGui::SetNextDock(ImGuiDockSlot_Bottom);// optional

				if (ImGui::BeginDock(tmp)) {
					ImGui::Text("Content of dock window %d goes here", i);

					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
					            ImGui::GetIO().Framerate);
				}
				ImGui::EndDock();

				continue;
			}

			if (ImGui::BeginDock(tmp)) {
				ImGui::Text("Content of dock window %d goes here", i);
			}
			ImGui::EndDock();
		}
		ImGui::EndDockspace();
	}
	ImGui::End();


	ImGui::xe::render();
}

void UILayer::update(float delta) {
	ImGui::xe::update(window, delta);

}

void UILayer::input(xe::Event &event) {
	ImGui::xe::processEvent(event);
}
