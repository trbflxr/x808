//
// Created by FLXR on 9/13/2018.
//

#include <cstring>
#include <xe/utils/logger.hpp>
#include <xe/common.hpp>
#include <xe/core/vfs.hpp>

#ifdef XE_PLATFORM_WINDOWS
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #ifndef WIN32_EXTRA_LEAN
    #define WIN32_EXTRA_LEAN
  #endif
  #include <windows.h>
#endif

extern "C" { XE_API uint64 NvOptimusEnablement = 0x00000001; }
extern "C" { XE_API int32 AmdPowerXpressRequestHighPerformance = 1; }

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

    XE_CORE_FATAL("Invalid render API '", api, "'");
    return RenderAPI::Invalid;
  }

  void initialize() {
#ifdef XE_PLATFORM_WINDOWS
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IONBF, 2048);
#endif
    Logger::get();

    VFS::init();
  }

  void shutdown() {
    VFS::shutdown();
  }

}