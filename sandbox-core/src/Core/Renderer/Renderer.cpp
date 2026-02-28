#include "Core/Renderer/Renderer.h"

namespace sb {

	Ref<Context> Renderer::m_Context = nullptr;

	void Renderer::Init(Ref<Context> context) {

		m_Context = context;
	}

	void Renderer::Shutdown() {


	}

	void Renderer::Begin() {


	}

	void Renderer::End() {


	}
}
