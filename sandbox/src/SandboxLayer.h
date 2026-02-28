#pragma once

#include <Core.h>

class SandboxLayer : public sb::Layer {

public:

	SandboxLayer()
		: sb::Layer("Sandbox")

	{}

	virtual ~SandboxLayer() = default;

	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate(sb::Time ts);
	virtual void OnImGuiRender();
	virtual void OnEvent(sb::Event& event);
};
