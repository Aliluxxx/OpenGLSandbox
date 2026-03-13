#include "Core/Base/Input.h"

#include "Core/Renderer/CameraController.h"

namespace sb {

	// Orthographic

	OrthographicCameraController::OrthographicCameraController(float aspect_ratio, float zoom_level, float near_plane, float far_plane)
		:
		m_Camera(-aspect_ratio * zoom_level, aspect_ratio * aspect_ratio, -aspect_ratio, zoom_level, near_plane, far_plane),
		m_AspectRatio(aspect_ratio),
		m_ZoomLevel(zoom_level)

	{}

	OrthographicCameraController::OrthographicCameraController(float near_plane, float far_plane)
		:
		m_Camera(-1.0f, 1.0f, -1.0f, 1.0f, near_plane, far_plane)

	{}

	void OrthographicCameraController::OnUpdate(Time ts) {

		const float deltaTime = ts.AsSeconds();

		Vector3f position = m_Camera.GetPosition();
		float rotation = m_Camera.GetRotation();

		if (Input::IsKeyPressed(Key::W))
			position.y += m_TranslationSpeed * deltaTime;

		else if (Input::IsKeyPressed(Key::S))
			position.y -= m_TranslationSpeed * deltaTime;

		if (Input::IsKeyPressed(Key::A))
			position.x -= m_TranslationSpeed * deltaTime;

		else if (Input::IsKeyPressed(Key::D))
			position.x += m_TranslationSpeed * deltaTime;

		if (Input::IsKeyPressed(Key::Q))
			rotation += m_RotationSpeed * deltaTime;

		if (Input::IsKeyPressed(Key::E))
			rotation -= m_RotationSpeed * deltaTime;

		m_Camera.SetPosition(position);
		m_Camera.SetRotation(rotation);
	}

	void OrthographicCameraController::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(SB_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	}

	void OrthographicCameraController::OnResize(float width, float height) {

		m_AspectRatio = width / height;
		m_Camera.SetRectangle(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	void OrthographicCameraController::SetTranslationSpeed(float speed) {

		m_TranslationSpeed = speed;
	}

	void OrthographicCameraController::SetRotationSpeed(float speed) {

		m_RotationSpeed = speed;
	}

	void OrthographicCameraController::SetZoomSensitivity(float sensitivity) {

		m_ZoomSensitivity = sensitivity;
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {

		m_ZoomLevel -= e.GetYOffset() * m_ZoomSensitivity * glm::abs(m_ZoomLevel);
		m_ZoomLevel = m_ZoomLevel < 0.0f ? m_ZoomSensitivity : m_ZoomLevel;
		m_Camera.SetRectangle(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return true;
	}

	// Fly

	FlyCameraController::FlyCameraController(float field_of_view, float aspect_ratio, float near_plane, float far_plane)
		: m_Camera(field_of_view, aspect_ratio, near_plane, far_plane)

	{}

	void FlyCameraController::OnUpdate(Time ts) {

		if (m_Disabled)
			return;

		const float deltaTime = ts.AsSeconds();

		Vector3f position = m_Camera.GetPosition();
		const Vector3f& front = m_Camera.GetFront();
		const Vector3f& up = m_Camera.GetUp();

		if (Input::IsKeyPressed(Key::LeftShift))
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
