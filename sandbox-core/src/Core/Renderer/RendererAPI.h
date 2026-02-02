#include "Core/Base/Base.h"
#include "Core/Renderer/Context.h"

namespace sb {

	class RendererAPI {

	public:

		RendererAPI(Ref<Context> context);

		void Init();
		void Shutdown();
		void Begin();
		void End();

		static Scope<RendererAPI> Create(Ref<Context> context);

	private:

		Ref<Context> m_Context;
	};
}
