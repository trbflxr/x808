#include <xe/app/application.hpp>
#include <xe/utils/log.hpp>
#include "test2d.hpp"
#include "test3d.hpp"
#include "debugui.hpp"

using namespace xe;

class Test : public xe::Application {
public:
	explicit Test(const xe::Config &config) :
			Application(config, RenderAPI::OPENGL, 330),
			ui(nullptr),
			t2d(nullptr),
			t3d(nullptr) {

		ui = new DebugUI();
		t2d = new Test2D();
//		t3d = new Test3D(ui);

		pushLayer(t2d);
//		pushLayer(t3d);
		pushLayer(ui);
	}

	~Test() override {
		delete ui;
		delete t2d;
		delete t3d;
	}

private:
	DebugUI *ui;
	Test2D *t2d;
	Test3D *t3d;
};

int main() {
	xe::Config config{ };
	xe::Config::load(config);

	Test test(config);
	test.start();

	return 0;
}