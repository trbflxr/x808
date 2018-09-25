//
// Created by FLXR on 9/7/2018.
//

#include <imgui_impl_xe_gl.hpp>
#include <xe/utils/log.hpp>
#include "uilayer.hpp"

using namespace xe;

UILayer::UILayer() {
	ImGui::xe::init(window);

	ImGui::StyleColorsDark();

	dockContext = ImGui::CreateDockContext();
	ImGui::SetCurrentDockContext((ImGui::DockContext *) dockContext);

	ImGui::LoadDock("dock.ini");

	XE_INFO(L"title: ", window.getTitle());
}

UILayer::~UILayer() {
	ImGui::SaveDock("dock.ini");

	ImGui::xe::shutdown();

	ImGui::DestroyDockContext((ImGui::DockContext *) dockContext);
}

void UILayer::render() {
//	static bool show_demo_window = true;
//	static bool show_another_window = false;
//	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//
//	{
//		static float f = 0.0f;
//		static int counter = 0;
//
//		ImGui::Begin("Hello, world!");
//
//		ImGui::Text("This is some useful text.");
//		ImGui::Checkbox("Demo Window", &show_demo_window);
//		ImGui::Checkbox("Another Window", &show_another_window);
//
//		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
//		ImGui::ColorEdit3("clear color", (float *) &clear_color);
//
//		if (ImGui::Button("Button"))
//			counter++;
//		ImGui::SameLine();
//		ImGui::Text("counter = %d", counter);
//
//		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
//		            ImGui::GetIO().Framerate);
//		ImGui::End();
//	}
//
//	if (show_another_window) {
//		ImGui::Begin("Another Window", &show_another_window);
//		ImGui::Text("Hello from another window!");
//		if (ImGui::Button("Close Me"))
//			show_another_window = false;
//		ImGui::End();
//	}
//
//	if (show_demo_window)
//		ImGui::ShowDemoWindow(&show_demo_window);

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

			if (i == 9) {
				ImGui::SetNextDock(ImGuiDockSlot_Bottom);// optional

				if (ImGui::BeginDock(tmp)) {
					ImGui::Text("Content of dock window %d goes here", i);
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
