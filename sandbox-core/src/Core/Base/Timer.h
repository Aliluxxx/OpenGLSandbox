#pragma once

#ifndef SB_PRECOMPILED_HEADER
#include <chrono>
#endif

#include "Core/Base/Base.h"
#include "Core/Base/Time.h"

namespace sb {

	class Timer {

	public:

		Timer();
		Timer(const Timer& other) = delete;

		void Restart();
		Time GetElapsedTime() const;

	private:

		std::chrono::time_point<std::chrono::steady_clock> m_Timer;
	};
}
