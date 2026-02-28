#pragma once

#ifndef SB_PRECOMPILED_HEADER
#include <glad/glad.h>
#endif

namespace sb {

	void __stdcall OpenGLDebuggerCallback(
		GLenum source,
		GLenum type,
		unsigned int id,
		GLenum severity,
		GLsizei length,
		const char* message,
		const void* user_param);
}
