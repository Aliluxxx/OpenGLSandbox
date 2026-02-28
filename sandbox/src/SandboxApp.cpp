#include <Core.h>

// ---------- Entry point ----------
#include <Core/Base/EntryPoint.h>
// ---------------------------------

#include "SandboxLayer.h"

class SandboxApp : public sb::Application {

public:

	SandboxApp(const sb::ApplicationSpecification& spec)
		: sb::Application(spec)

	{

		PushLayer(sb::CreateRef<SandboxLayer>());
	}

	~SandboxApp() {}
};

sb::Application* sb::CreateApplication(sb::ApplicationCommandLineArgs args) {

	ApplicationSpecification spec;
	spec.Name = "OpenGL";
	spec.WorkingDirectory = ".";
	spec.CommandLineArgs = args;
	sb::Log::GetClientLogger()->set_level(spdlog::level::trace);

	return new SandboxApp(spec);
}
