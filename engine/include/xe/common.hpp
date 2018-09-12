//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_COMMON_HPP
#define X808_COMMON_HPP

#include <cstring>

#ifdef _WIN32
	#define XE_PLATFORM_WINDOWS
#endif


#ifdef XE_PLATFORM_WINDOWS
	#ifdef XE_STATIC
		#define XE_API __declspec(dllexport)
	#else
		#define XE_API __declspec(dllimport)
	#endif
#endif


#define BIT(x) (1 << (x))


enum class RenderAPI {
	OpenGL, Direct3D, Invalid
};

static const char *renderApiToString(RenderAPI api) {
	switch (api) {
		case RenderAPI::OpenGL: return "ogl";
		case RenderAPI::Direct3D: return "d3d";
		default: return "Invalid";
	}
}

static RenderAPI stringToRenderApi(const char *api) {
	if (strcmp(api, "ogl") == 0) return RenderAPI::OpenGL;
	if (strcmp(api, "d3d") == 0) return RenderAPI::Direct3D;
	return RenderAPI::Invalid;
}

#endif //X808_COMMON_HPP
