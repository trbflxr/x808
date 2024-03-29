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


#if defined(__clang__) || defined(__GNUC__)
  #define XE_FMT_ARGS(fmt) __attribute__((format(printf, fmt, fmt + 1)))
  #define XE_FMT_LIST(fmt) __attribute__((format(printf, fmt, 0)))
#else
  #define XE_FMT_ARGS(fmt)
  #define XE_FMT_LIST(fmt)
#endif


//logger
#define XE_LOG_LEVEL_FATAL  0
#define XE_LOG_LEVEL_ERROR  1
#define XE_LOG_LEVEL_WARN   2
#define XE_LOG_LEVEL_INFO   3
#define XE_LOG_LEVEL_TRACE  4

#define XE_LOG_LEVEL XE_LOG_LEVEL_TRACE


#define XE_CORE   BIT(0)
#define XE_CLIENT BIT(1)

namespace xe {

  enum class RenderAPI {
    OpenGL, Direct3D, Invalid
  };

  XE_API const char *renderApiToString(RenderAPI api);
  XE_API RenderAPI stringToRenderApi(const char *api);

  XE_API void initialize();
  XE_API void shutdown();

}

#endif //X808_COMMON_HPP
