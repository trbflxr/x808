#include <application/application.hpp>
#include <utils/log.hpp>
#include "testecs.hpp"
#include "test3d.hpp"
#include "debugui.hpp"

using namespace xe;

class Test : public xe::Application {
public:
	explicit Test(const xe::Config &config) :
			Application(config, gfx::api::RenderAPI::OPENGL) {

		ui = new DebugUI();

//		pushLayer(new TestECS());
		pushLayer(new Test3D(ui));
		pushLayer(ui);
	}

	~Test() override {
		delete ui;
	}

private:
	DebugUI *ui;
};

int main() {
	xe::Config config{ };
	xe::Config::load(config);

	Test test(config);
	test.start();

	return 0;
}