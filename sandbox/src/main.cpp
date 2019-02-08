#include <xe/app/application.hpp>
#include <xe/utils/logger.hpp>
#include <xe/core/vfs.hpp>
#include <xe/core/filesystem.hpp>
#include "test2d.hpp"
#include "test3d.hpp"
#include "debugui.hpp"
#include "testb2d.hpp"
#include "testl2d.hpp"


static void writeKeyValue(xe::Config &config, const char *key, const char *value) {
	if (strcmp(key, "width") == 0) {
		config.width = (uint) atoi(value);
	} else if (strcmp(key, "height") == 0) {
		config.height = (uint) atoi(value);
	} else if (strcmp(key, "fullScreen") == 0) {
		config.fullScreen = (bool) atoi(value);
	} else if (strcmp(key, "vSync") == 0) {
		config.vSync = (bool) atoi(value);
	} else if (strcmp(key, "ups") == 0) {
		config.ups = (uint) atoi(value);
	} else if (strcmp(key, "fps") == 0) {
		config.fps = (uint) atoi(value);
	} else if (strcmp(key, "srgb") == 0) {
		config.useSRGB = (bool) atoi(value);
	} else if (strcmp(key, "renderApi") == 0) {
		config.renderApi = xe::stringToRenderApi(value);
	} else if (strcmp(key, "apiVersion") == 0) {
		config.apiVersion = (uint) atoi(value);
	} else if (strcmp(key, "maxTextureUnits") == 0) {
		config.maxTextureUnits = (uint) atoi(value);
	}
}

static bool loadConfig(xe::Config &config, const char *path) {
	int64 size = xe::FileSystem::size(path);
	if (size == -1) return false;

	xe::string cfg(size, '\0');

	bool r = xe::FileSystem::read(path, &cfg[0], size);
	if (!r) return false;

	std::vector<xe::string> lines = xe::splitString(cfg, "\n\r");

	const char *search = "=";
	for (auto &&l : lines) {
		char *key = strtok(&l[0], search);
		char *value = strtok(nullptr, search);

		writeKeyValue(config, key, value);
	}

	return true;
}


#include <xe/systems/system.hpp>
class S0 : public xe::System {
public:
	void render() override {
		XE_TRACE("s0 render");
	}

	void update(float delta) override {
		XE_TRACE("s0 update");
	}
};
class S1 : public xe::System {
public:
	void render() override {
		XE_TRACE("S1 render");
	}

	void update(float delta) override {
		XE_TRACE("S1 update");
	}
};
class S2 : public xe::System {
public:
	void render() override {
		XE_TRACE("S2 render");
	}

	void update(float delta) override {
		XE_TRACE("S2 update");
	}
};

class Test : public xe::Application {
public:
	explicit Test(const xe::Config &config) :
			Application(config, "Sandbox🌍"),
			ui(nullptr),
			t2d(nullptr),
			t3d(nullptr),
			tb2d(nullptr),
			tl2d(nullptr) {

		xe::VFS::mount("fonts", "xe_sandbox_assets/fonts/");
		xe::VFS::mount("textures", "xe_sandbox_assets/textures/");
		xe::VFS::mount("shaders", "/");

		ui = new DebugUI();
//		t3d = new Test3D(ui);
//		t2d = new Test2D();
		tl2d = new TestL2D();
//		tb2d = new TestB2D();

//		pushLayer(tb2d);
		pushLayer(tl2d);
//		pushLayer(t2d);
//		pushLayer(t3d);
		pushOverlay(ui);


		S0 *s0 = new S0();
		S1 *s1 = new S1();
		S2 *s2 = new S2();

		pushSystem(s0);
		pushSystem(s1);
		pushSystem(s2);
	}

	~Test() override { }

private:
	DebugUI *ui;
	Test2D *t2d;
	Test3D *t3d;
	TestB2D *tb2d;
	TestL2D *tl2d;
};

int main() {
	xe::initialize();

	xe::Config config;
	loadConfig(config, "xeconfig");

	Test test(config);
	test.start();

	xe::shutdown();

	return 0;
}
