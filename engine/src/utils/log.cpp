//
// Created by FLXR on 2/2/2019.
//

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <xe/utils/log.hpp>

namespace xe {

	std::shared_ptr<spdlog::logger> Log::coreLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;

	void Log::initialize() {
		spdlog::set_pattern("%^[%T] %n: %v%$");

		coreLogger = spdlog::stdout_color_mt("XE");
		coreLogger->set_level(spdlog::level::trace);

		clientLogger = spdlog::stdout_color_mt("App");
		clientLogger->set_level(spdlog::level::trace);
	}

	void Log::shutdown() {
		spdlog::shutdown();
	}

	void Log::setCoreLogLevel(LogLevel level) {
		coreLogger->set_level(static_cast<spdlog::level::level_enum>(level));
	}

	void Log::setClientLogLevel(LogLevel level) {
		clientLogger->set_level(static_cast<spdlog::level::level_enum>(level));
	}

};