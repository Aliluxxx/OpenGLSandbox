#include "Core/Base/Time.h"

const sb::Time sb::Time::Zero;
const sb::Time sb::Time::Infinity((sb::Int64)0x80000000);

#include "Sleep.h"

namespace sb {

	void Sleep(Time duration) {

		std::this_thread::sleep_for(std::chrono::microseconds(duration.AsMicroseconds()));
	}
}
