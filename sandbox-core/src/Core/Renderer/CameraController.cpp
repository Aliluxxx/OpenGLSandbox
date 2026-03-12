#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Base/Input.h"

#include "Core/Renderer/CameraController.h"

namespace sb{

	FlyCameraController::FlyCameraController(float field_of_view, float aspect_ratio, float near_plane, float far_plane)
		: m_Camera(field_of_view, aspect_ratio, near_plane, far_plane), m_Speed(10.0f), m_Sensitivity(0.1f)

	{}

	void FlyCameraController::OnUpdate(Time ts) {

		if (m_Disabled)
			return;

		const float deltaTime = ts.AsSeconds();

		Vector3f position = m_Camera.GetPosition();
		const Vector3f& front = m_Camera.GetFront();
		const Vector3f& up = m_Camera.GetUp();

		if (Input::IsKeyPressed(Key::Q))
			m_Speed = 1.0f;
		else
			m_Speed = 10.0f;

		if (Input::IsKeyPressed(Key::W))
			position += front * m_Speed * deltaTime;

		else if (Input::IsKeyPressed(Key::S))
			position -= front * m_Speed * deltaTime;

		if (Input::IsKeyPressed(Key::A))
			position -= glm::normalize(glm::cross(front, up)) * m_Speed * deltaTime;

		else if (Input::IsKeyPressed(Key::D))
			position += glm::normalize(glm::cross(front, up)) * m_Speed * deltaTime;

		m_Camera.SetPosition(position);
	}

	void FlyCameraController::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(SB_BIND_EVENT_FN(FlyCameraController::OnWindowResized));
		if (!m_Disabled)
			dispatcher.Dispatch<MouseMovedEvent>(SB_BIND_EVENT_FN(FlyCameraController::OnMouseMoved));
	}

	void FlyCameraController::OnResize(float width, float height) {

		m_Camera.SetAspectRatio(width / height);
	}

	void FlyCameraController::SetSpeed(float speed) {

		m_Speed = speed;
	}

	void FlyCameraController::SetSensitivity(float sensitivity) {

		m_Sensitivity = sensitivity;
	}

	void FlyCameraController::SetCameraMovementDisabled(bool disable) {

		m_Disabled = disable;
		m_FirstMouse = true;
	}

	bool FlyCameraController::OnWindowResized(WindowResizeEvent& e) {

		OnResize((float)e.GetWidth(), (float)e.GetHeight());

		return true;
	}

	bool FlyCameraController::OnMouseMoved(MouseMovedEvent& e) {

		if (m_FirstMouse) {

			m_LastXPos = e.GetX();
			m_LastYPos = e.GetY();
			m_FirstMouse = false;
		}

		float xoffset = e.GetX() - m_LastXPos;
		float yoffset = m_LastYPos - e.GetY();
		m_LastXPos = e.GetX();
		m_LastYPos = e.GetY();

		xoffset *= m_Sensitivity;
		yoffset *= m_Sensitivity;

		m_Camera.SetPitch(m_Camera.GetPitch() + yoffset);
		m_Camera.SetYaw(m_Camera.GetYaw() + xoffset);

		return true;
	}
}
