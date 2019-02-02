//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_LOG_HPP
#define X808_LOG_HPP


#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/math/math.hpp>

namespace xe {

	enum class LogLevel {
		Trace = 0,
		Debug,
		Info,
		Warn,
		Error,
		Fatal,
		Off
	};

	class XE_API Log {
	public:
		static XE_API void initialize();
		static XE_API void shutdown();

		static XE_API void setCoreLogLevel(LogLevel level);
		static XE_API void setClientLogLevel(LogLevel level);

		static inline std::shared_ptr<spdlog::logger> &getCoreLogger() { return coreLogger; }
		static inline std::shared_ptr<spdlog::logger> &getClientLogger() { return clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};

	template<typename OStream>
	OStream &operator<<(OStream &os, const vec2 &v) {
		return os << "vec2(" << v.x << ", " << v.y << ")";
	}

	template<typename OStream>
	OStream &operator<<(OStream &os, const vec3 &v) {
		return os << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
	}

	template<typename OStream>
	OStream &operator<<(OStream &os, const vec4 &v) {
		return os << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	}

	template<typename OStream>
	OStream &operator<<(OStream &os, const quat &v) {
		return os << "quat(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	}

	template<typename OStream>
	OStream &operator<<(OStream &os, const mat4 &m) {
		os << "\n\tmat4({"
		   << m.elements[0] << ", " << m.elements[1] << ", " << m.elements[2] << ", " << m.elements[3] << "},\n\t     {"
		   << m.elements[4] << ", " << m.elements[5] << ", " << m.elements[6] << ", " << m.elements[7] << "},\n\t     {"
		   << m.elements[8] << ", " << m.elements[9] << ", " << m.elements[10] << ", " << m.elements[11] << "},\n\t     {"
		   << m.elements[12] << ", " << m.elements[13] << ", " << m.elements[14] << ", " << m.elements[15] << "})";
		return os;
	}
}


#define XE_CORE_TRACE(...)    ::xe::Log::getCoreLogger()->trace(__VA_ARGS__)
#define XE_CORE_INFO(...)     ::xe::Log::getCoreLogger()->info(__VA_ARGS__)
#define XE_CORE_WARN(...)     ::xe::Log::getCoreLogger()->warn(__VA_ARGS__)
#define XE_CORE_ERROR(...)    ::xe::Log::getCoreLogger()->error(__VA_ARGS__)
#define XE_CORE_FATAL(...)    ::xe::Log::getCoreLogger()->critical(__VA_ARGS__)


#define XE_TRACE(...)        ::xe::Log::getClientLogger()->trace(__VA_ARGS__)
#define XE_INFO(...)         ::xe::Log::getClientLogger()->info(__VA_ARGS__)
#define XE_WARN(...)         ::xe::Log::getClientLogger()->warn(__VA_ARGS__)
#define XE_ERROR(...)        ::xe::Log::getClientLogger()->error(__VA_ARGS__)
#define XE_FATAL(...)        ::xe::Log::getClientLogger()->critical(__VA_ARGS__)


#endif //X808_LOG_HPP
