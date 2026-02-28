#pragma once

#include "Core/Base/Base.h"
#include "Core/Base/Log.h"

#ifdef SB_ENABLE_ASSERTS
	#define SB_ASSERT(x, ...) if(!(x)) { SB_ERROR ("Assertion Failed: {0}", __VA_ARGS__); SB_DEBUGBREAK(); }
#else
	#define SB_ASSERT(x, ...) 0;
#endif
