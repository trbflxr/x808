#include <xe/app/application.hpp>
#include <xe/core/vfs.hpp>
#include "debugui.hpp"
#include "maker.hpp"

using namespace xe;

class AtlasMaker : public Application {
public:
	explicit AtlasMaker(const Config &config) :
			Application(config, "AtlasMaker") {

		VFS::mount("textures", "xe_sandbox_assets/textures/");

		DebugUI *ui = new DebugUI();
		Maker *m = new Maker();

		pushLayer(m);
		pushOverlay(ui);
	}

	~AtlasMaker() override { }

private:

};

int main() {
	initialize();

	Config config;
	config.width = 1280;
	config.height = 720;
	config.fullScreen = false;
	config.vSync = true;
	config.ups = 30;
	config.fps = 90;
	config.useSRGB = true;
	config.renderApi = RenderAPI::OpenGL;
	config.apiVersion = 330;
	config.maxPointLights2D = 1;

	AtlasMaker test(config);
	test.start();

	shutdown();

	return 0;
}
