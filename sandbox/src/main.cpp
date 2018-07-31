#include <application/application.hpp>
#include <utils/log.hpp>
#include "testecs.hpp"
#include "test3d.hpp"
#include "testui.hpp"

using namespace xe;

class Test : public xe::Application {
public:
	explicit Test(const xe::Config &config) :
			Application(config, gfx::api::RenderAPI::OPENGL) { }

	~Test() override { }

	void init() override {
		Application::init();

		TestUI *ui = new TestUI();

//		pushLayer(new TestECS());
		pushLayer(new Test3D(ui));
//		pushLayer(ui);
	}

};

int main() {

	xe::Config config{ };
	xe::Config::load(config);

	Test test(config);
	test.start();

	return 0;
}