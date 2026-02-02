#include "SandboxLayer.h"

#include <glad/glad.h>

void SandboxLayer::OnAttach() {


}

void SandboxLayer::OnDetach() {


}

sb::GamepadID id;

void SandboxLayer::OnUpdate(sb::Time ts) {

	sb::Sleep(sb::Milliseconds(1));
}

void SandboxLayer::OnImGuiRender() {


}

void SandboxLayer::OnEvent(sb::Event& event) {


	sb::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<sb::KeyPressedEvent>([](sb::KeyPressedEvent& event) {

		switch (event.GetKeyCode()) {

			case sb::Key::Escape:
				sb::Application::Close();
				break;
		}

		return false;
	});

	SB_TRACE("{0}", event.ToString());
}
