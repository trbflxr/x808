#include <application/application.hpp>
#include <utils/log.hpp>
#include "test2d.hpp"
#include "test3d.hpp"
#include "test3ddeferred.hpp"
#include "debugui.hpp"

using namespace xe;

class Test : public xe::Application {
public:
	explicit Test(const xe::Config &config) :
			Application(config, api::RenderAPI::OPENGL, 450) {

		ui = new DebugUI();

//		pushLayer(new Test2D());
		pushLayer(new Test3D(ui));
//		pushLayer(new Test3DDeferred());
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