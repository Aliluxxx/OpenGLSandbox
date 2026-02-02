#pragma once

#ifndef SB_PRECOMPILED_HEADER
#include <string>
#endif

#include "Core/Base/Base.h"

namespace sb {

	struct ContextSpecification {

		void* WindowPtr = nullptr;
		bool EnableDebug = true;
		std::string AppName = "";
		std::string EngineName = "";
	};

	class Context {

	public:

		Context(const ContextSpecification& spec);

		void Init();
		void Destroy();
		void BeginFrame();
		void EndFrame();

		inline const ContextSpecification& GetSpecification() const { return m_Specification; }

		static Ref<Context> Create(const ContextSpecification& spec = ContextSpecification());

	private:

		ContextSpecification m_Specification;
	};
}
