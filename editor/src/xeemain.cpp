//
// Created by FLXR on 9/7/2018.
//

#include <xe/app/application.hpp>
#include "uilayer.hpp"

class Editor : public xe::Application {
public:
	explicit Editor(const xe::Config &config) :
			Application(config, L"XE Editor"),
			ui(nullptr) {

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

	xe::Config config{ };
	xe::Config::load(config);

	Editor editor(config);
	editor.start();

	xe::shutdown();

	return 0;
}