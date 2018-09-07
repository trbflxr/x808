//
// Created by FLXR on 9/7/2018.
//

#include <xe/app/application.hpp>
#include "uilayer.hpp"

class Editor : public xe::Application {
public:
	explicit Editor(const xe::Config &config) :
			Application(config, xe::RenderAPI::OPENGL, 330),
			ui(nullptr) {

		ui = new UILayer();

		pushLayer(ui);
	}

	~Editor() override {
		delete ui;
	}

private:
	UILayer *ui;
};

int main() {
	xe::Config config{ };
	xe::Config::load(config);

	Editor editor(config);
	editor.start();

	return 0;
}