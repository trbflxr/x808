//
// Created by FLXR on 9/13/2018.
//

#include <cstring>
#include <xe/utils/log.hpp>
#include <xe/common.hpp>

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

	XE_FATAL(L"[Core]: Invalid render API '", api, L"'");
	return RenderAPI::Invalid;
}
