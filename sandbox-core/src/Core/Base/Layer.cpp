#include "Core/Base/Layer.h"

namespace sb {

#ifdef SB_DIST
	Layer::Layer(const std::string& debug_name) {}
#else
	Layer::Layer(const std::string& debug_name)
		: m_DebugName(debug_name)
	{}
#endif

	Layer::~Layer() {}
}
