#pragma once

#include "Core/Base/Base.h"
#include "Core/Base/Time.h"
#include "Core/Events/Event.h"
#include "Core/Renderer/Camera.h"

namespace sb {

	class CameraController {

	public:

		virtual void OnUpdate(Time ts) = 0;
		virtual void OnEvent(Event& e) = 0;
		virtual void OnResize(float width, float height) = 0;
	};

	class FlyCameraController : public CameraController {

	public:

		FlyCameraController(float field_of_view, float aspect_ratio, float near_plane, float far_plane);

		virtual void OnUpdate(Time ts) override;
		virtual void OnEvent(Event& e) override;
		virtual void OnResize(float width, float height) override;

		void SetSpeed(float speed);
		inline const float GetSpeed() const { return m_Speed; }
		void SetSensitivity(float sensitivity);
		inline const float GetSensitivity() const { return m_Sensitivity; }
		inline sb::Matrix4f GetViewProjectionMatrix() { return m_Camera.GetProjectionMatrix() * m_Camera.GetViewMatrix(); }
		void SetCameraMovementDisabled(bool disable);
		inline const FlyCamera& GetCamera() const { return m_Camera; }

	protected:

		bool OnWindowResized(WindowResizeEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);

		FlyCamera m_Camera;
		float m_Speed;
		float m_Sensitivity;

	private:

		bool m_FirstMouse = true;
		float m_LastXPos = 0.0f;
		float m_LastYPos = 0.0f;
		bool m_Disabled = false;
	};
}
