#pragma once

#include "Core/Renderer/Context.h"
#include "Core/Renderer/RendererAPI.h"

namespace sb {

	class Renderer {

	public:

		static void Init(Ref<Context> context);
		static void Shutdown();

		static void Begin();
		static void End();

	private:

		static Scope<RendererAPI> s_RendererAPI;
	};
}
