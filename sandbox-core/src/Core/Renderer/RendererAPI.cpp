#include "Core/Renderer/RendererAPI.h"

namespace sb {

	RendererAPI::RendererAPI(Ref<Context> context)
		: m_Context(context)
	{}

	void RendererAPI::Begin() {


	}

	void RendererAPI::End() {


	}

	Scope<RendererAPI> RendererAPI::Create(Ref<Context> context) {

		return Scope<RendererAPI>();
	}
}
