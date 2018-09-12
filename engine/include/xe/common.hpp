//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_COMMON_HPP
#define X808_COMMON_HPP

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

XE_API const char *renderApiToString(RenderAPI api);
XE_API RenderAPI stringToRenderApi(const char *api);

#endif //X808_COMMON_HPP
