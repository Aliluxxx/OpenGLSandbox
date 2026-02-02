#pragma once

#define FMT_UNICODE 0
#undef SPDLOG_ACTIFM_LEFML
#define SPDLOG_ACTIFM_LEFML SPDLOG_LEFML_TRACE
#define SPDLOG_ACTIVE_LEVEL 0
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace sb {

	class Log {

	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetOpenGLLogger() { return s_OpenGLLogger; }

	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_OpenGLLogger;
	};
}

#if defined(SB_DIST)
	#define SB_TRACE(...)
	#define SB_INFO(...)
	#define SB_WARN(...)
	#define SB_ERROR(...)
	#define SB_CRITICAL(...)
#else
	#define SB_TRACE(...)         SPDLOG_LOGGER_TRACE(::sb::Log::GetClientLogger(), __VA_ARGS__)
	#define SB_INFO(...)          SPDLOG_LOGGER_INFO(::sb::Log::GetClientLogger(), __VA_ARGS__)
	#define SB_WARN(...)          SPDLOG_LOGGER_WARN(::sb::Log::GetClientLogger(), __VA_ARGS__)
	#define SB_ERROR(...)         SPDLOG_LOGGER_ERROR(::sb::Log::GetClientLogger(), __VA_ARGS__)
	#define SB_CRITICAL(...)      SPDLOG_LOGGER_CRITICAL(::sb::Log::GetClientLogger(), __VA_ARGS__)
#endif
