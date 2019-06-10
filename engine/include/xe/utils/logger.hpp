//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_LOGGER_HPP
#define X808_LOGGER_HPP


#include <cstring>
#include <utility>
#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/utils/singleton.hpp>

#define XE_LOG_BUFFER_SIZE 4096

namespace xe {

  class XE_API Logger : public Singleton<Logger> {
  public:
    template<typename... Args>
    void logMessage(uint sender, uint level, Args... args) {
      char buffer[XE_LOG_BUFFER_SIZE];
      uint position = 0;

      static const char *xe = "[XE]:\t";
      static const char *client = "[Client]:\t";

      if (sender == XE_CORE) {
        const size_t length = strlen(xe);
        memcpy(&buffer[position], &xe[0], length);
        position += length;
      } else {
        const size_t length = strlen(client);
        memcpy(&buffer[position], &client[0], length);
        position += length;
      }

      buildLogMessage(buffer, position, std::forward<Args>(args)...);

      buffer[position++] = '\n';
      buffer[position] = '\0';

      logMessage(level, buffer);

    }

  private:
    void logMessage(uint level, const char *message);
    void platformLogMessage(uint level, const char *message);

    template<typename T>
    const char *toString(const T &t);

    template<typename First>
    void buildLogMessage(char *buffer, uint &position, First &&first) {
      const char *formatted = toString<First>(first);
      size_t length = strlen(formatted);

      memcpy(&buffer[position], &formatted[0], length);
      position += length;
    }

    template<typename First, typename... Args>
    void buildLogMessage(char *buffer, uint &position, First &&first, Args &&... args) {
      const char *formatted = toString<First>(first);
      size_t length = strlen(formatted);

      memcpy(&buffer[position], &formatted[0], length);
      position += length;

      if (sizeof...(Args)) {
        buildLogMessage(buffer, position, std::forward<Args>(args)...);
      }
    }

  private:
    char buffer[XE_LOG_BUFFER_SIZE];
  };

}


//core
#if XE_LOG_LEVEL >= XE_LOG_LEVEL_FATAL
  #define XE_CORE_FATAL(...)  ::xe::Logger::get().logMessage(XE_CORE, XE_LOG_LEVEL_FATAL, ##__VA_ARGS__)
#else
  #define XE_CORE_FATAL(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_ERROR
  #define XE_CORE_ERROR(...)  ::xe::Logger::get().logMessage(XE_CORE, XE_LOG_LEVEL_ERROR, ##__VA_ARGS__)
#else
  #define XE_CORE_ERROR(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_WARN
  #define XE_CORE_WARN(...)  ::xe::Logger::get().logMessage(XE_CORE, XE_LOG_LEVEL_WARN, ##__VA_ARGS__)
#else
  #define XE_CORE_WARN(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_INFO
  #define XE_CORE_INFO(...)  ::xe::Logger::get().logMessage(XE_CORE, XE_LOG_LEVEL_INFO, ##__VA_ARGS__)
#else
  #define XE_CORE_INFO(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_TRACE
  #define XE_CORE_TRACE(...)  ::xe::Logger::get().logMessage(XE_CORE, XE_LOG_LEVEL_TRACE, ##__VA_ARGS__)
#else
  #define XE_CORE_TRACE(...)
#endif


//client
#if XE_LOG_LEVEL >= XE_LOG_LEVEL_FATAL
  #define XE_FATAL(...)  ::xe::Logger::get().logMessage(XE_CLIENT, XE_LOG_LEVEL_FATAL, ##__VA_ARGS__)
#else
  #define XE_FATAL(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_ERROR
  #define XE_ERROR(...)  ::xe::Logger::get().logMessage(XE_CLIENT, XE_LOG_LEVEL_ERROR, ##__VA_ARGS__)
#else
  #define XE_ERROR(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_WARN
  #define XE_WARN(...)  ::xe::Logger::get().logMessage(XE_CLIENT, XE_LOG_LEVEL_WARN, ##__VA_ARGS__)
#else
  #define XE_WARN(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_INFO
  #define XE_INFO(...)  ::xe::Logger::get().logMessage(XE_CLIENT, XE_LOG_LEVEL_INFO, ##__VA_ARGS__)
#else
  #define XE_INFO(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_TRACE
  #define XE_TRACE(...)  ::xe::Logger::get().logMessage(XE_CLIENT, XE_LOG_LEVEL_TRACE, ##__VA_ARGS__)
#else
  #define XE_TRACE(...)
#endif


#endif //X808_LOGGER_HPP
