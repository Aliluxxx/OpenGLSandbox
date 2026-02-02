#include "spdlog/sinks/stdout_color_sinks.h"

#include "Core/Renderer/OpenGLDebuggerCallback.h"

namespace sb {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::shared_ptr<spdlog::logger> Log::s_OpenGLLogger;

	void Log::Init() {

		s_CoreLogger = spdlog::stdout_color_mt("CORE");
		s_CoreLogger->set_pattern("[%T.%e][%n][%s:%#][%^%l%$]: %v");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_pattern("[%T.%e][%s:%#][%^%l%$]: %v");
		s_ClientLogger->set_level(spdlog::level::trace);

		s_OpenGLLogger = spdlog::stdout_color_mt("OPENGL");
		s_OpenGLLogger->set_pattern("[%T:%e][%n][%^%l%$]: %v");
		s_OpenGLLogger->set_level(spdlog::level::warn);
	}

	void __stdcall OpenGLDebuggerCallback(
		GLenum source,
		GLenum type,
		unsigned int id,
		GLenum severity,
		GLsizei length,
		const char* message,
		const void* user_param)

	{

		//Ignore non-significant error/warning codes
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

		std::string sourceStr;
		std::string typeStr;

		switch (source) {

			case GL_DEBUG_SOURCE_API:             sourceStr = "API"; break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceStr = "WINDOW SYSTEM"; break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "SHADER COMPILER"; break;
			case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceStr = "THIRD PARTY"; break;
			case GL_DEBUG_SOURCE_APPLICATION:     sourceStr = "APPLICATION"; break;
			case GL_DEBUG_SOURCE_OTHER:           sourceStr = "OTHER"; break;
		}

		switch (type) {

			case GL_DEBUG_TYPE_ERROR:               typeStr = "ERROR"; break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "DEPRECATED BEHAVIOR"; break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeStr = "UNDEFINED BEHAVIOR"; break;
			case GL_DEBUG_TYPE_PORTABILITY:         typeStr = "PORTABILITY"; break;
			case GL_DEBUG_TYPE_PERFORMANCE:         typeStr = "PERFORMANCE"; break;
			case GL_DEBUG_TYPE_MARKER:              typeStr = "MARKER"; break;
			case GL_DEBUG_TYPE_PUSH_GROUP:          typeStr = "PUSH GROUP"; break;
			case GL_DEBUG_TYPE_POP_GROUP:           typeStr = "POP GROUP"; break;
			case GL_DEBUG_TYPE_OTHER:               typeStr = "OTHER"; break;
		}

		switch (severity) {

			case GL_DEBUG_SEVERITY_HIGH:
				sb::Log::GetOpenGLLogger()->error("({0} | {1}) {2}", typeStr, sourceStr, message);
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				sb::Log::GetOpenGLLogger()->warn("({0} | {1}) {2}", typeStr, sourceStr, message);
				break;
			case GL_DEBUG_SEVERITY_LOW:
				sb::Log::GetOpenGLLogger()->info("({0} | {1}) {2}", typeStr, sourceStr, message);
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				sb::Log::GetOpenGLLogger()->trace("({0} | {1}) {2}", typeStr, sourceStr, std::string(message));
				break;
		}
	}
}
