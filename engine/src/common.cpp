//
// Created by FLXR on 9/13/2018.
//

#include <cstring>
#include <xe/utils/log.hpp>
#include <xe/common.hpp>
#include <xe/core/vfs.hpp>

#ifdef XE_PLATFORM_WINDOWS
	#include <windows.h>
#endif

namespace xe {

	const char *renderApiToString(RenderAPI api) {
		switch (api) {
			case RenderAPI::OpenGL: return "ogl";
			case RenderAPI::Direct3D: return "d3d";
			default: return "Invalid";
		}
	}

	RenderAPI stringToRenderApi(const char *api) {
		if (strcmp(api, "ogl") == 0) return RenderAPI::OpenGL;
		if (strcmp(api, "d3d") == 0) return RenderAPI::Direct3D;

		XE_CORE_FATAL("Invalid render API '{0}'", api);
		return RenderAPI::Invalid;
	}

	void initialize() {
#ifdef XE_PLATFORM_WINDOWS
		SetConsoleOutputCP(CP_UTF8);
		setvbuf(stdout, nullptr, _IONBF, 2048);
#endif

		Log::initialize();

		VFS::init();
	}

	void shutdown() {
		VFS::shutdown();

		Log::shutdown();
	}

}