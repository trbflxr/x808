//
// Created by FLXR on 11/14/2018.
//

#include <xe/systems/shell.hpp>
#include <imgui/impl/imgui_impl_xe_gl.hpp>

namespace xe {

	Shell::Shell() {
		createDefaultCommands();

		ImGui::xe::init(window);

		ImGui::StyleColorsDark();
	}

	Shell::~Shell() {

		ImGui::xe::shutdown();
	}

	void Shell::render() {

		static bool open = true;
		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
		bool opt_fullscreen = opt_fullscreen_persistant;


		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen) {
			ImGuiViewport *viewport = ImGui::GetMainViewport();
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
				if (ImGui::MenuItem("Close DockSpace", nullptr, false, &open)) {
					open = false;
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();

		ImGui::xe::render();
	}

	void Shell::update(float delta) {
		if (active) {
			ImGui::xe::update(window, delta);
		}
	}

	void Shell::input(Event &event) {
		if (active) {
			ImGui::xe::processEvent(event);
		}

		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Tilde) {
				string s = commands["hello"](false);
				wprintf(L"%s\n", s.c_str());
			}
		}
	}

	void Shell::processCommand(const string &command) {

	}

	bool Shell::addCommand(const string &command, const std::function<string(bool hint)> &callback) {
		return false;
	}

	void Shell::createDefaultCommands() {
		commands["hello"] = [=](bool hint) {
			active = !active;
			if (hint) return "Prints 'Hello'.";
			return "Hello";
		};
	}

}