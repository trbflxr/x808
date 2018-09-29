//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_LOG_HPP
#define X808_LOG_HPP


#include <codecvt>
#include <locale>
#include <cstring>
#include <string>
#include <xe/common.hpp>
#include <xe/gfx/context.hpp>
#include <xe/math/math.hpp>

#define XE_LOG_LEVEL_FATAL 0
#define XE_LOG_LEVEL_ERROR 1
#define XE_LOG_LEVEL_WARN  2
#define XE_LOG_LEVEL_INFO  3


namespace std {
	template<typename T>
	wstring to_wstring(const T &t) {
		static wstring_convert <std::codecvt_utf8_utf16<wchar_t>> converter;
		const wstring name = converter.from_bytes(typeid(T).name());

		return wstring(L"[Unsupported type (") + name + wstring(L")] ");
	}
}


namespace xe { namespace internal {

	static wchar_t buffer[1024 * 10];
	static std::wstring str;

	XE_API void platformLogMessage(uint level, const wchar_t *message);

	template<typename T>
	static const wchar_t *to_wstring(const T &t) { return std::to_wstring(t).c_str(); }

	template<>
	inline const wchar_t *to_wstring<wchar_t>(const wchar_t &t) {
		str = t;
		return str.c_str();
	}

	template<>
	inline const wchar_t *to_wstring<wchar_t *>(wchar_t *const &t) { return t; }

	template<>
	inline const wchar_t *to_wstring<const wchar_t *>(const wchar_t *const &t) { return t; }

	template<>
	inline const wchar_t *to_wstring<std::wstring>(const std::wstring &t) { return t.c_str(); }

	template<>
	inline const wchar_t *to_wstring<std::wstring_view>(const std::wstring_view &t) { return t.data(); }

	template<>
	inline const wchar_t *to_wstring<char>(const char &t) {
		str = t;
		return str.c_str();
	}

	template<>
	inline const wchar_t *to_wstring<char *>(char *const &t) {
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		str = converter.from_bytes(t);
		return str.c_str();
	}

	template<>
	inline const wchar_t *to_wstring<const char *>(const char *const &t) {
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		str = converter.from_bytes(t);
		return str.c_str();
	}

	template<>
	inline const wchar_t *to_wstring<std::string>(const std::string &t) {
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		str = converter.from_bytes(t);
		return str.c_str();
	}

	template<>
	inline const wchar_t *to_wstring<std::string_view>(const std::string_view &t) {
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		str = converter.from_bytes(t.data());
		return str.c_str();
	}

	template<>
	inline const wchar_t *to_wstring<bool>(const bool &t) { return t ? L"true" : L"false"; }

	template<>
	inline const wchar_t *to_wstring<uint8>(const uint8 &t) {
		swprintf(buffer, L"%d", t);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<int8>(const int8 &t) {
		swprintf(buffer, L"%d", t);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<uint16>(const uint16 &t) {
		swprintf(buffer, L"%d", t);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<int16>(const int16 &t) {
		swprintf(buffer, L"%d", t);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<uint32>(const uint32 &t) {
		swprintf(buffer, L"%d", t);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<int32>(const int32 &t) {
		swprintf(buffer, L"%d", t);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<uint64>(const uint64 &t) {
		swprintf(buffer, L"%llu", t);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<int64>(const int64 &t) {
		swprintf(buffer, L"%lli", t);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<float>(const float &t) {
		swprintf(buffer, L"%.5f", t);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<double>(const double &t) {
		swprintf(buffer, L"%.5f", t);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<vec2>(const vec2 &t) {
		swprintf(buffer, L"vec2(%.3f, %.3f)", t.x, t.y);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<vec3>(const vec3 &t) {
		swprintf(buffer, L"vec3(%.3f, %.3f, %.3f)", t.x, t.y, t.z);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<vec4>(const vec4 &t) {
		swprintf(buffer, L"vec4(%.3f, %.3f, %.3f, %.3f)", t.x, t.y, t.z, t.w);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<vec2i>(const vec2i &t) {
		swprintf(buffer, L"vec2i(%d, %d)", t.x, t.y);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<vec2f>(const vec2f &t) {
		swprintf(buffer, L"vec2f(%f, %f)", t.x, t.y);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<quat>(const quat &t) {
		swprintf(buffer, L"quat(%.3f, %.3f, %.3f, %.3f)", t.x, t.y, t.z, t.w);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<mat4>(const mat4 &t) {
		swprintf(buffer, L"mat4({%.3f, %.3f, %.3f, %.3f},\n"
		                 L"\t   {%.3f, %.3f, %.3f, %.3f},\n"
		                 L"\t   {%.3f, %.3f, %.3f, %.3f},\n"
		                 L"\t   {%.3f, %.3f, %.3f, %.3f})",
		         t.elements[0], t.elements[1], t.elements[2], t.elements[3],
		         t.elements[4], t.elements[5], t.elements[6], t.elements[7],
		         t.elements[8], t.elements[9], t.elements[10], t.elements[11],
		         t.elements[12], t.elements[13], t.elements[14], t.elements[15]);
		return buffer;
	}

	template<>
	inline const wchar_t *to_wstring<GAPIInfo>(const GAPIInfo &t) {
		swprintf(buffer, L"Context:\n"
		                 L"\t - Vendor:            %s\n"
		                 L"\t - Version:           %s\n"
		                 L"\t - Renderer:          %s\n"
		                 L"\t - Shading language:  %s\n"
		                 L"\t - Max texture size:  %i\n"
		                 L"\t - Max texture units: %i\n"
		                 L"\t - Max image units:   %i\n",
		         t.vendor,
		         t.version,
		         t.renderer,
		         t.shadingLevel,
		         t.maxTexSize,
		         t.maxTexUnits,
		         t.maxTexImgUnits);

		return buffer;
	}


	template<typename First>
	static void print_log_internal(wchar_t *buffer, uint &position, First &&first) {
		const std::wstring formatted = xe::internal::to_wstring<First>(first);
		size_t length = formatted.size();

		memcpy(&buffer[position], &formatted[0], length * 2);
		position += length;
	}

	template<typename First, typename... Args>
	static void print_log_internal(wchar_t *buffer, uint &position, First &&first, Args &&... args) {
		const std::wstring formatted = xe::internal::to_wstring<First>(first);
		size_t length = formatted.size();

		memcpy(&buffer[position], &formatted[0], length * 2);
		position += length;

		if (sizeof...(Args)) {
			print_log_internal(buffer, position, std::forward<Args>(args)...);
		}
	}

	template<typename... Args>
	static void log_message(uint level, bool newline, Args... args) {
		wchar_t buffer[1024 * 10];
		uint position = 0;

		print_log_internal(buffer, position, std::forward<Args>(args)...);

		if (newline) {
			buffer[position++] = L'\n';
		}

		buffer[position] = 0;

		platformLogMessage(level, buffer);
	}

}}


#ifndef XE_LOG_LEVEL
#define XE_LOG_LEVEL XE_LOG_LEVEL_INFO
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_FATAL
#define XE_FATAL(...) xe::internal::log_message(XE_LOG_LEVEL_FATAL, true, L"XE:    ", ##__VA_ARGS__)
#define _XE_FATAL(...) xe::internal::log_message(XE_LOG_LEVEL_FATAL, false, ##__VA_ARGS__)
#else
#define XE_FATAL(...)
#define _XE_FATAL(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_ERROR
#define XE_ERROR(...) xe::internal::log_message(XE_LOG_LEVEL_ERROR, true, L"XE:    ", ##__VA_ARGS__)
#define _XE_ERROR(...) xe::internal::log_message(XE_LOG_LEVEL_ERROR, false, ##__VA_ARGS__)
#else
#define XE_ERROR(...)
#define _XE_ERROR(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_WARN
#define XE_WARN(...) xe::internal::log_message(XE_LOG_LEVEL_WARN, true, L"XE:    ", ##__VA_ARGS__)
#define _XE_WARN(...) xe::internal::log_message(XE_LOG_LEVEL_WARN, false, ##__VA_ARGS__)
#else
#define XE_WARN(...)
#define _XE_WARN(...)
#endif

#if XE_LOG_LEVEL >= XE_LOG_LEVEL_INFO
#define XE_INFO(...) xe::internal::log_message(XE_LOG_LEVEL_INFO, true, L"XE:    ", ##__VA_ARGS__)
#define _XE_INFO(...) xe::internal::log_message(XE_LOG_LEVEL_INFO, false, ##__VA_ARGS__)
#else
#define XE_INFO(...)
#define _XE_INFO(...)
#endif

#ifdef XE_DEBUG
#define XE_ASSERT(x, ...) \
        if (!(x)) {\
            XE_FATAL(L"ASSERTION FAILED"); \
            XE_FATAL(__FILE__, L": ", __LINE__); \
            XE_FATAL(L"Condition: ", #x); \
            XE_FATAL(__VA_ARGS__); \
            __debugbreak(); \
        }
#else
#define XE_ASSERT(x, ...)
#endif

#endif //X808_LOG_HPP
