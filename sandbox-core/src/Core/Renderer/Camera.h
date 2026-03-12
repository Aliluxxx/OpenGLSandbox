#pragma once

#include "Core/Base/Base.h"

namespace sb {

	class Camera {

	public:

		Camera() = default;

		void SetPosition(const Vector3f& position);
		inline const Vector3f& GetPosition() const { return m_Position; }

		virtual Matrix4f GetProjectionMatrix() = 0;
		virtual Matrix4f GetViewMatrix() = 0;

	protected:

		Vector3f m_Position = Vector3f(0.0f, 0.0f, 0.0f);
	};

	// Orthographic

	class OrthographicCamera : public Camera {

	public:

		OrthographicCamera(float left, float right, float bottom, float top, float aspect_ratio = 1.0f, float zoom = 0.0f);

		void SetRotation(float rotation);
		inline const float& GetRotation() const { return m_Rotation; }
		void SetAspectRatio(float aspect_ratio);
		inline float GetAspectRatio() const { return m_AspectRatio; }

		virtual Matrix4f GetProjectionMatrix() override;
		virtual Matrix4f GetViewMatrix() override;

	protected:

		float m_Rotation = 0.0f;
		float m_Left = -1.0f;
		float m_Right = 1.0f;
		float m_Bottom = -1.0f;
		float m_Top = 1.0f;
		float m_AspectRatio = 1.0f;
		float m_Zoom = 0.0f;
	};

	// Perspective

	class PerspectiveCamera : public Camera {

	public:

		PerspectiveCamera(float field_of_view, float aspect_ratio, float near_plane, float far_plane);

		void SetFieldOfView(float field_of_view);
		inline float GetFieldOfView() const { return m_FieldOfView; }
		void SetAspectRatio(float aspect_ratio);
		inline float GetAspectRatio() const { return m_AspectRatio; }
		void SetNearPlane(float near_plane);
		inline float GetNearPlane() const { return m_NearPlane; }
		void SetFarPlane(float far_plane);
		inline float GetFarPlane() const { return m_FarPlane; }
		void SetFront(const Vector3f& front);
		inline const Vector3f& GetFront() const { return m_Front; }
		void SetUp(const Vector3f& up);
		inline const Vector3f& GetUp() const { return m_Up; }

		virtual Matrix4f GetProjectionMatrix() override;
		virtual Matrix4f GetViewMatrix() override;

	protected:

		float m_FieldOfView = glm::radians(90.0f);
		float m_AspectRatio = 1.0f;
		float m_NearPlane = 0.1f;
		float m_FarPlane = 100.0f;
		Vector3f m_Front = Vector3f(0.0f, 0.0f, -1.0f);
		Vector3f m_Up = Vector3f(0.0f, 1.0f, 0.0f);
	};

	// Fly

	class FlyCamera : public PerspectiveCamera {

	public:

		FlyCamera(float field_of_view, float aspect_ratio, float near_plane, float far_plane);

		void SetPitch(float pitch);
		inline float GetPitch() const { return m_Pitch; }
		void SetYaw(float yaw);
		inline float GetYaw() const { return m_Yaw; }

		virtual Matrix4f GetViewMatrix() override;

	protected:

		float m_Pitch = 0.0f;
		float m_Yaw = -90.0f;
	};
}
