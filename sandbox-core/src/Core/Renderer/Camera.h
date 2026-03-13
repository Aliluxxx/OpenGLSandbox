#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

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

		OrthographicCamera(float left, float right, float bottom, float top, float near_plane = -1.0f, float far_plane = 1.0f);
		OrthographicCamera() = default;

		void SetRectangle(float left, float right, float bottom, float top, float near_plane = NAN, float far_plane = NAN);
		void SetLeft(float left);
		inline float GetLeft() const { return m_Left; }
		void SetRight(float right);
		inline float GetRight() const { return m_Right; }
		void SetBottom(float bottom);
		inline float GetBottom() const { return m_Bottom; }
		void SetTop(float top);
		inline float GetTop() const { return m_Top; }
		void SetNearPlane(float near_plane);
		inline float GetNearPlane() const { return m_NearPlane; }
		void SetFarPlane(float far_plane);
		inline float GetFarPlane() const { return m_FarPlane; }

		virtual Matrix4f GetProjectionMatrix() override;
		virtual Matrix4f GetViewMatrix() override;

	protected:

		float m_Left = -1.0f;
		float m_Right = 1.0f;
		float m_Bottom = -1.0f;
		float m_Top = 1.0f;
		float m_NearPlane = -1.0f;
		float m_FarPlane = 1.0f;
	};

	// Perspective

	class PerspectiveCamera : public Camera {

	public:

		PerspectiveCamera(float field_of_view, float aspect_ratio, float near_plane, float far_plane);
		PerspectiveCamera() = default;

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
		FlyCamera() = default;

		void SetPitch(float pitch);
		inline float GetPitch() const { return m_Pitch; }
		void SetYaw(float yaw);
		inline float GetYaw() const { return m_Yaw; }

		virtual Matrix4f GetViewMatrix() override;

	protected:

		float m_Pitch = 0.0f;
		float m_Yaw = -90.0f;
	};

	// Editor

	class EditorCamera : public Camera {

	public:

		EditorCamera(float field_of_view, float near_plane, float far_plane);
		EditorCamera() = default;

		void SetFieldOfView(float field_of_view);
		inline float GetFieldOfView() const { return m_FieldOfView; }
		inline float GetAspectRatio() const { return m_Viewport.x / m_Viewport.y; }
		void SetNearPlane(float near_plane);
		inline float GetNearPlane() const { return m_NearPlane; }
		void SetFarPlane(float far_plane);
		inline float GetFarPlane() const { return m_FarPlane; }
		void SetPitch(float pitch);
		inline float GetPitch() const { return m_Pitch; }
		void SetYaw(float yaw);
		inline float GetYaw() const { return m_Yaw; }
		void SetDistance(float distance);
		inline float GetDistance() const { return m_Distance; }
		void SetViewportSize(float width, float height);
		inline const Vector2f& GetViewport() const { return m_Viewport; }
		void SetFocalPoint(const Vector3f& focal_point);
		inline const Vector3f& GetFocalPoint() const { return m_FocalPoint; }
		Vector3f GetUpDirection() const;
		Vector3f GetRightDirection() const;
		Vector3f GetForwardDirection() const;
		glm::quat GetOrientation() const;

		virtual Matrix4f GetProjectionMatrix() override;
		virtual Matrix4f GetViewMatrix() override;

	protected:

		float m_FieldOfView = glm::radians(90.0f);
		float m_NearPlane = 0.1f;
		float m_FarPlane = 100.0f;
		float m_Pitch = 0.0f;
		float m_Yaw = 0.0f;
		float m_Distance = 10.0f;
		Vector2f m_Viewport = Vector2f(0.0f, 0.0f);
		Vector3f m_FocalPoint = { 0.0f, 0.0f, 0.0f };
	};
}
