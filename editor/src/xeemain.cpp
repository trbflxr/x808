//
// Created by FLXR on 9/7/2018.
//

#include <xe/app/application.hpp>
#include <xe/core/vfs.hpp>
#include "uilayer.hpp"

class Editor : public xe::Application {
public:
	explicit Editor(const xe::Config &config) :
			Application(config, "XE Editor"),
			ui(nullptr) {

		xe::VFS::mount("fonts", "xe_sandbox_assets/fonts/");
		xe::VFS::mount("textures", "xe_sandbox_assets/textures/");

		ui = new xe::UILayer();

		pushLayer(ui);
	}

	~Editor() override {
		delete ui;
	}

private:
	xe::UILayer *ui;
};

int main() {
	xe::initialize();

	xe::Config config;
	config.width = 1280;
	config.height = 720;
	config.fullScreen = false;
	config.vSync = false;
	config.ups = 30;
	config.fps = 0;
	config.useSRGB = true;
	config.renderApi = xe::RenderAPI::OpenGL;
	config.apiVersion = 430;
	config.maxTextureUnits = 0;
	config.maxPointLights2D = 50;

	Editor editor(config);
	editor.start();

	xe::shutdown();

	return 0;
}