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


#define XE_LOG_LEVEL_FATAL  0
#define XE_LOG_LEVEL_ERROR  1
#define XE_LOG_LEVEL_WARN   2
#define XE_LOG_LEVEL_INFO   3
#define XE_LOG_LEVEL_TRACE  4

#define XE_LOGGER_BUFFER_SIZE 4096

namespace xe {

	class XE_API Logger : public Singleton<Logger> {
	public:
		template<typename... Args>
		void logMessage(uint level, bool newline, Args... args) {
			char buffer[XE_LOGGER_BUFFER_SIZE];
			uint position = 0;

			printLogInternal(buffer, position, std::forward<Args>(args)...);

			if (newline) {
				buffer[position++] = '\n';
			}

			buffer[position] = '\0';

			platformLogMessage(level, buffer);
		}

	private:
		void platformLogMessage(uint level, const char *message);

		template<typename T>
		const char *toString(const T &t);

		template<typename First>
		void printLogInternal(char *buffer, uint &position, First &&first) {
			const char* formatted = toString<First>(first);
			size_t length = strlen(formatted);

			memcpy(&buffer[position], &formatted[0], length);
			position += length;
		}

		template<typename First, typename... Args>
		void printLogInternal(char *buffer, uint &position, First &&first, Args &&... args) {
			const char* formatted = toString<First>(first);
			size_t length = strlen(formatted);

			memcpy(&buffer[position], &formatted[0], length);
			position += length;

			if (sizeof...(Args)) {
				printLogInternal(buffer, position, std::forward<Args>(args)...);
			}
		}

	private:
		char buffer[XE_LOGGER_BUFFER_SIZE];
	};

}

#ifndef XE_LOG_LEVEL
#define XE_LOG_LEVEL XE_LOG_LEVEL_INFO
#endif

//core
#if XE_LOG_LEVEL >= XE_LOG_LEVEL_FATAL
#define XE_CORE_FATAL(...)  ::xe::Logger::get().logMessage(XE_LOG_LEVEL_FATAL, true, "XE:    ", ##__VA_ARGS__)
#define _XE_CORE_FATAL(...) ::xe::Logger::get().logMessage(XE_LOG_LEVEL_FATAL, false, ##__VA_ARGS__)
#else
#define XE_CORE_FATAL(...)
#define _XE_CORE_FATAL(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_ERROR
#define XE_CORE_ERROR(...)  ::xe::Logger::get().logMessage(XE_LOG_LEVEL_ERROR, true, "XE:    ", ##__VA_ARGS__)
#define _XE_CORE_ERROR(...) ::xe::Logger::get().logMessage(XE_LOG_LEVEL_ERROR, false, ##__VA_ARGS__)
#else
#define XE_CORE_ERROR(...)
#define _XE_CORE_ERROR(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_WARN
#define XE_CORE_WARN(...)  ::xe::Logger::get().logMessage(XE_LOG_LEVEL_WARN, true, "XE:    ", ##__VA_ARGS__)
#define _XE_CORE_WARN(...) ::xe::Logger::get().logMessage(XE_LOG_LEVEL_WARN, false, ##__VA_ARGS__)
#else
#define XE_CORE_WARN(...)
#define _XE_CORE_WARN(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_INFO
#define XE_CORE_INFO(...)  ::xe::Logger::get().logMessage(XE_LOG_LEVEL_INFO, true, "XE:    ", ##__VA_ARGS__)
#define _XE_CORE_INFO(...) ::xe::Logger::get().logMessage(XE_LOG_LEVEL_INFO, false, ##__VA_ARGS__)
#else
#define XE_CORE_INFO(...)
#define _XE_CORE_INFO(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_TRACE
#define XE_CORE_TRACE(...)  ::xe::Logger::get().logMessage(XE_LOG_LEVEL_TRACE, true, "XE:    ", ##__VA_ARGS__)
#define _XE_CORE_TRACE(...) ::xe::Logger::get().logMessage(XE_LOG_LEVEL_TRACE, false, ##__VA_ARGS__)
#else
#define XE_CORE_TRACE(...)
#define _XE_CORE_TRACE(...)
#endif


//client
#if XE_LOG_LEVEL >= XE_LOG_LEVEL_FATAL
#define XE_FATAL(...)  ::xe::Logger::get().logMessage(XE_LOG_LEVEL_FATAL, true, "Client:    ", ##__VA_ARGS__)
#define _XE_FATAL(...) ::xe::Logger::get().logMessage(XE_LOG_LEVEL_FATAL, false, ##__VA_ARGS__)
#else
#define XE_FATAL(...)
#define _XE_FATAL(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_ERROR
#define XE_ERROR(...)  ::xe::Logger::get().logMessage(XE_LOG_LEVEL_ERROR, true, "Client:    ", ##__VA_ARGS__)
#define _XE_ERROR(...) ::xe::Logger::get().logMessage(XE_LOG_LEVEL_ERROR, false, ##__VA_ARGS__)
#else
#define XE_ERROR(...)
#define _XE_ERROR(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_WARN
#define XE_WARN(...)  ::xe::Logger::get().logMessage(XE_LOG_LEVEL_WARN, true, "Client:    ", ##__VA_ARGS__)
#define _XE_WARN(...) ::xe::Logger::get().logMessage(XE_LOG_LEVEL_WARN, false, ##__VA_ARGS__)
#else
#define XE_WARN(...)
#define _XE_WARN(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_INFO
#define XE_INFO(...)  ::xe::Logger::get().logMessage(XE_LOG_LEVEL_INFO, true, "Client:    ", ##__VA_ARGS__)
#define _XE_INFO(...) ::xe::Logger::get().logMessage(XE_LOG_LEVEL_INFO, false, ##__VA_ARGS__)
#else
#define XE_INFO(...)
#define _XE_INFO(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_TRACE
#define XE_TRACE(...)  ::xe::Logger::get().logMessage(XE_LOG_LEVEL_TRACE, true, "Client:    ", ##__VA_ARGS__)
#define _XE_TRACE(...) ::xe::Logger::get().logMessage(XE_LOG_LEVEL_TRACE, false, ##__VA_ARGS__)
#else
#define XE_TRACE(...)
#define _XE_TRACE(...)
#endif


#endif //X808_LOGGER_HPP
