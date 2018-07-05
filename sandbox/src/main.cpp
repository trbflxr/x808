#include <application/application.hpp>
#include <utils/log.hpp>
#include "test2d.hpp"

using namespace xe;

class Test : public xe::Application {
public:
	explicit Test(const xe::Config &config) :
			Application(config, gfx::api::RenderAPI::OPENGL) { }

	~Test() override { }

	void init() override {
		Application::init();

		pushLayer(new Test2D());
	}

};

int main() {

	xe::Config config{ };
	xe::Config::load(config);

	Test test(config);
	test.start();

	return 0;
}