//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_LOG_HPP
#define X808_LOG_HPP


#include <cstring>
#include <string>
#include "common.hpp"
#include "math/math.hpp"

#define XE_LOG_LEVEL_FATAL 0
#define XE_LOG_LEVEL_ERROR 1
#define XE_LOG_LEVEL_WARN  2
#define XE_LOG_LEVEL_INFO  3


namespace std {
	template<typename T>
	string to_string(const T &t) { return string("[Unsupported type (") + typeid(T).name() + string(")]"); }
}


//todo: support more types
namespace xe { namespace internal {

	static char buffer[1024 * 10];

	XE_API void platformLogMessage(uint level, const char *message);

	template<typename T>
	static const char *to_string(const T &t) { return std::to_string(t).c_str(); }

	template<>
	inline const char *to_string<char>(const char &t) { return &t; }

	template<>
	inline const char *to_string<char *>(char *const &t) { return t; }

	template<>
	inline const char *to_string<const char *>(const char *const &t) { return t; }

	template<>
	inline const char *to_string<std::string>(const std::string &t) { return t.c_str(); }

	template<>
	inline const char *to_string<std::string_view>(const std::string_view &t) { return t.data(); }

	template<>
	inline const char *to_string<bool>(const bool &t) { return t ? "true" : "false"; }

	template<>
	inline const char *to_string<uint8>(const uint8 &t) {
		sprintf(buffer, "%d", t);
		return buffer;
	}

	template<>
	inline const char *to_string<int8>(const int8 &t) {
		sprintf(buffer, "%d", t);
		return buffer;
	}

	template<>
	inline const char *to_string<uint16>(const uint16 &t) {
		sprintf(buffer, "%d", t);
		return buffer;
	}

	template<>
	inline const char *to_string<int16>(const int16 &t) {
		sprintf(buffer, "%d", t);
		return buffer;
	}

	template<>
	inline const char *to_string<vec2>(const vec2 &t) {
		sprintf(buffer, "vec2(%.3f, %.3f)", t.x, t.y);
		return buffer;
	}

	template<>
	inline const char *to_string<vec3>(const vec3 &t) {
		sprintf(buffer, "vec3(%.3f, %.3f, %.3f)", t.x, t.y, t.z);
		return buffer;
	}

	template<>
	inline const char *to_string<vec4>(const vec4 &t) {
		sprintf(buffer, "vec4(%.3f, %.3f, %.3f, %.3f)", t.x, t.y, t.z, t.w);
		return buffer;
	}

	template<>
	inline const char *to_string<vec2u>(const vec2u &t) {
		sprintf(buffer, "vec2u(%d, %d)", t.x, t.y);
		return buffer;
	}


	template<typename First>
	static void print_log_internal(char *buffer, uint &position, First &&first) {
		const char *formatted = xe::internal::to_string<First>(first);
		size_t length = strlen(formatted);

		memcpy(&buffer[position], formatted, length);
		position += length;
	}

	template<typename First, typename... Args>
	static void print_log_internal(char *buffer, uint &position, First &&first, Args &&... args) {
		const char *formatted = xe::internal::to_string<First>(first);
		size_t length = strlen(formatted);

		memcpy(&buffer[position], formatted, length);
		position += length;

		if (sizeof...(Args)) {
			print_log_internal(buffer, position, std::forward<Args>(args)...);
		}
	}

	template<typename... Args>
	static void log_message(uint level, bool newline, Args... args) {
		char buffer[1024 * 10];
		uint position = 0;

		print_log_internal(buffer, position, std::forward<Args>(args)...);

		if (newline) {
			buffer[position++] = '\n';
		}

		buffer[position] = 0;

		platformLogMessage(level, buffer);
	}

}}


#ifndef XE_LOG_LEVEL
#define XE_LOG_LEVEL XE_LOG_LEVEL_INFO
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_FATAL
#define XE_FATAL(...) xe::internal::log_message(XE_LOG_LEVEL_FATAL, true, "XE:    ", __VA_ARGS__)
#define _XE_FATAL(...) xe::internal::log_message(XE_LOG_LEVEL_FATAL, false, __VA_ARGS__)
#else
#define XE_FATAL(...)
#define _XE_FATAL(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_ERROR
#define XE_ERROR(...) xe::internal::log_message(XE_LOG_LEVEL_ERROR, true, "XE:    ", __VA_ARGS__)
#define _XE_ERROR(...) xe::internal::log_message(XE_LOG_LEVEL_ERROR, false, __VA_ARGS__)
#else
#define XE_ERROR(...)
#define _XE_ERROR(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_WARN
#define XE_WARN(...) xe::internal::log_message(XE_LOG_LEVEL_WARN, true, "XE:    ", __VA_ARGS__)
#define _XE_WARN(...) xe::internal::log_message(XE_LOG_LEVEL_WARN, false, __VA_ARGS__)
#else
#define XE_WARN(...)
#define _XE_WARN(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_INFO
#define XE_INFO(...) xe::internal::log_message(XE_LOG_LEVEL_INFO, true, "XE:    ", __VA_ARGS__)
#define _XE_INFO(...) xe::internal::log_message(XE_LOG_LEVEL_INFO, false, __VA_ARGS__)
#else
#define XE_INFO(...)
#define _XE_INFO(...)
#endif

#ifdef XE_DEBUG
#define XE_ASSERT(x, ...) \
        if (!(x)) {\
            XE_FATAL("ASSERTION FAILED"); \
            XE_FATAL(__FILE__, ": ", __LINE__); \
            XE_FATAL("Condition: ", #x); \
            XE_FATAL("Args: ", #__VA_ARGS__); \
            __debugbreak(); \
        }
#else
#define XE_ASSERT(x, ...)
#endif

#endif //X808_LOG_HPP
