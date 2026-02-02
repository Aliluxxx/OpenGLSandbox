#include "Core/Renderer/Renderer.h"

namespace sb {

	Scope<RendererAPI> Renderer::s_RendererAPI = nullptr;

	void Renderer::Init(Ref<Context> context) {

		s_RendererAPI = RendererAPI::Create(context);
	}

	void Renderer::Shutdown() {


	}

	void Renderer::Begin() {

		s_RendererAPI->Begin();
	}

	void Renderer::End() {

		s_RendererAPI->End();
	}
}
