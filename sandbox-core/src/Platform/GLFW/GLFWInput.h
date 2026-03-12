#pragma once

#include "Core/Base/Base.h"
#include "Core/Base/Input.h"

namespace sb {

	class GLFWWindow;

	class GLFWInput : public Input {

	protected:

		virtual bool IsKeyPressedImpl(KeyCode keycode) override;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) override;
		virtual void SetMousePositionImpl(Vector2f position) override;
		virtual Vector2i GetMousePositionImpl() override;
		virtual void SetMouseXImpl(float x) override;
		virtual float GetMouseXImpl() override;
		virtual void SetMouseYImpl(float y) override;
		virtual float GetMouseYImpl() override;
		virtual Vector2f GetGamepadAxisOffsetImpl(GamepadID id, GamepadAxisCode axis) override;
		virtual float GetGamepadAxisXOffsetImpl(GamepadID id, GamepadAxisCode axis) override;
		virtual float GetGamepadAxisYOffsetImpl(GamepadID id, GamepadAxisCode axis) override;
		virtual bool IsGamepadButtonPressedImpl(GamepadID id, GamepadButtonCode button) override;

	private:

		friend GLFWWindow;
	};
}
