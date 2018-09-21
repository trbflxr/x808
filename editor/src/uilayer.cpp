//
// Created by FLXR on 9/7/2018.
//

#include <imgui_impl_xe_gl.hpp>
#include "uilayer.hpp"

using namespace xe;

UILayer::UILayer() {
	ImGui::xe::init(window);

	ImGui::StyleColorsDark();
}

UILayer::~UILayer() {
	ImGui::xe::shutdown();
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

	ImGui::xe::render();
}

void UILayer::update(float delta) {
	ImGui::xe::update(window, delta);

	if(ImGui::Begin("Dock Demo"))
	{
		// dock layout by hard-coded or .ini file
		ImGui::BeginDockspace();

		if(ImGui::BeginDock("Dock 1")){
			ImGui::Text("I'm Wubugui!");
		}
		ImGui::EndDock();

		if(ImGui::BeginDock("Dock 2")){
			ImGui::Text("I'm BentleyBlanks!");
		}
		ImGui::EndDock();

		if(ImGui::BeginDock("Dock 3")){
			ImGui::Text("I'm LonelyWaiting!");
		}
		ImGui::EndDock();

		ImGui::EndDockspace();
	}
	ImGui::End();

	// multiple dockspace supported
	if(ImGui::Begin("Dock Demo2"))
	{
		ImGui::BeginDockspace();

		if(ImGui::BeginDock("Dock 2")){
			ImGui::Text("Who's your daddy?");
		}
		ImGui::EndDock();

		ImGui::EndDockspace();
	}
	ImGui::End();
}

void UILayer::input(xe::Event &event) {
	ImGui::xe::processEvent(event);
}
