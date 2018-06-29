#include <application/application.hpp>

using namespace xe;

class Test : public xe::Application {
public:
	explicit Test(const xe::Config &config) :
			Application(config) { }

	~Test() override { }

	void init() override {
		Application::init();
	}

};

int main() {
	xe::Config config{ };
	xe::Config::load(config);

	Test test(config);
	test.start();

	return 0;
}