#include "Core/Renderer/Camera.h"

namespace sb {

	void Camera::SetPosition(const Vector3f& position) {

		m_Position = position;
	}

	// Orthographic

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near_plane, float far_plane)
		:
		m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top),
		m_NearPlane(near_plane), m_FarPlane(far_plane)

	{}

	void OrthographicCamera::SetRectangle(float left, float right, float bottom, float top, float near_plane, float far_plane) {

		m_Left = left;
		m_Right = right;
		m_Bottom = bottom;
		m_Top = top;
		m_NearPlane = isnan(near_plane) ? m_NearPlane : near_plane;
		m_FarPlane = isnan(far_plane) ? m_FarPlane : far_plane;
	}

	void OrthographicCamera::SetRotation(float rotation) {

		m_Rotation = rotation;
	}

	void OrthographicCamera::SetLeft(float left) {

		m_Left = left;
	}

	void OrthographicCamera::SetRight(float right) {

		m_Right = right;
	}

	void OrthographicCamera::SetBottom(float bottom) {

		m_Bottom = bottom;
	}

	void OrthographicCamera::SetTop(float top) {

		m_Top = top;
	}

	void OrthographicCamera::SetNearPlane(float near_plane) {

		m_NearPlane = near_plane;
	}

	void OrthographicCamera::SetFarPlane(float far_plane) {

		m_FarPlane = far_plane;
	}

	Matrix4f OrthographicCamera::GetProjectionMatrix() {

		return glm::ortho(m_Left, m_Right, m_Bottom, m_Top, m_NearPlane, m_FarPlane);
	}

	Matrix4f OrthographicCamera::GetViewMatrix() {

		Matrix4f transform = glm::translate(Matrix4f(1.0f), m_Position) *
			glm::rotate(Matrix4f(1.0f), m_Rotation, Vector3f(0.0f, 0.0f, 1.0f));

		return glm::inverse(transform);
	}

	// Perspective

	PerspectiveCamera::PerspectiveCamera(float field_of_view, float aspect_ratio, float near_plane, float far_plane)
		:
		m_FieldOfView(field_of_view),
		m_AspectRatio(aspect_ratio),
		m_NearPlane(near_plane),
		m_FarPlane(far_plane)

	{}

	void PerspectiveCamera::SetFieldOfView(float field_of_view) {

		m_FieldOfView = field_of_view;
	}

	void PerspectiveCamera::SetAspectRatio(float aspect_ratio) {

		m_AspectRatio = aspect_ratio;
	}

	void PerspectiveCamera::SetNearPlane(float near_plane) {

		m_NearPlane = near_plane;
	}

	void PerspectiveCamera::SetFarPlane(float far_plane) {

		m_FarPlane = far_plane;
	}

	void PerspectiveCamera::SetFront(const Vector3f& front) {

		m_Front = front;
	}

	void PerspectiveCamera::SetUp(const Vector3f& up) {

		m_Up = up;
	}

	Matrix4f PerspectiveCamera::GetProjectionMatrix() {

		return glm::perspective(m_FieldOfView, m_AspectRatio, m_NearPlane, m_FarPlane);
	}

	Matrix4f PerspectiveCamera::GetViewMatrix() {

		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	// Fly

	FlyCamera::FlyCamera(float field_of_view, float aspect_ratio, float near_plane, float far_plane)
		: PerspectiveCamera(field_of_view, aspect_ratio, near_plane, far_plane)

	{}

	void FlyCamera::SetPitch(float pitch) {

		if (pitch > 89.0f)
			pitch = 89.0f;
		else if (pitch < -89.0f)
			pitch = -89.0f;
		else
			m_Pitch = pitch;
	}

	void FlyCamera::SetYaw(float yaw) {

		m_Yaw = yaw;
	}

	Matrix4f FlyCamera::GetViewMatrix() {

		Vector3f direction{};
		direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.y = sin(glm::radians(m_Pitch));
		direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(direction);

		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}
}
