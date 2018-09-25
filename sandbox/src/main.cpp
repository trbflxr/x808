#include <xe/app/application.hpp>
#include <xe/utils/log.hpp>
#include "test2d.hpp"
#include "test3d.hpp"
#include "debugui.hpp"
#include "testb2d.hpp"

class Test : public xe::Application {
public:
	explicit Test(const xe::Config &config) :
			Application(config),
			ui(nullptr),
			t2d(nullptr),
			t3d(nullptr),
			tb2d(nullptr){

		ui = new DebugUI();
//		t3d = new Test3D(ui);
//		t2d = new Test2D();
		tb2d = new TestB2D();

		pushLayer(tb2d);
//		pushLayer(t2d);
//		pushLayer(t3d);
		pushLayer(ui);
	}

	~Test() override {
		delete ui;
		delete t2d;
		delete t3d;
		delete tb2d;
	}

private:
	DebugUI *ui;
	Test2D *t2d;
	Test3D *t3d;
	TestB2D *tb2d;
};

int main() {
	xe::Config config{ };
	xe::Config::load(config);

	Test test(config);
	test.start();

	return 0;
}
