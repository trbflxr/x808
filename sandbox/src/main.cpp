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
	} else if (strcmp(key, "maxPointLights2D") == 0) {
		config.maxPointLights2D = (uint) atoi(value);
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

class Test : public xe::Application {
public:
	explicit Test(const xe::Config &config) :
			Application(config, "Sandbox🌍") {

		xe::VFS::mount("fonts", "xe_sandbox_assets/fonts/");
		xe::VFS::mount("textures", "xe_sandbox_assets/textures/");
		xe::VFS::mount("audio", "xe_sandbox_assets/audio/");
		xe::VFS::mount("shaders", "/");

		DebugUI *ui = new DebugUI();
//		Test3D *t3d = new Test3D(ui);
//		Test2D *t2d = new Test2D();
		TestL2D *tl2d = new TestL2D();
//		TestB2D *tb2d = new TestB2D();

//		pushLayer(tb2d);
		pushLayer(tl2d);
//		pushLayer(t2d);
//		pushLayer(t3d);
		pushOverlay(ui);
	}

	~Test() override { }

private:

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
