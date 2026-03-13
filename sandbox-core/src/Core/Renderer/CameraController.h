#pragma once

#include "Core/Base/Base.h"
#include "Core/Base/Time.h"
#include "Core/Events/Event.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Renderer/Camera.h"

namespace sb {

	class CameraController {

	public:

		virtual void OnUpdate(Time ts) = 0;
		virtual void OnEvent(Event& e) = 0;
		virtual void OnResize(float width, float height) = 0;
	};

	// Orthographic

	class OrthographicCameraController : public CameraController {

	public:

		OrthographicCameraController(float aspect_ratio, float zoom_level, float near_plane, float far_plane);
		OrthographicCameraController(float near_plane = -1.0f, float far_plane = 1.0f);
		OrthographicCameraController() = default;

		virtual void OnUpdate(Time ts) override;
		virtual void OnEvent(Event& e) override;
		virtual void OnResize(float width, float height) override;

		inline const OrthographicCamera& GetCamera() const { return m_Camera; }
		inline sb::Matrix4f GetViewProjectionMatrix() { return m_Camera.GetProjectionMatrix() * m_Camera.GetViewMatrix(); }

		void SetTranslationSpeed(float speed);
		inline float GetTranslationSpeed() const { return m_TranslationSpeed; }
		void SetRotationSpeed(float speed);
		inline float GetRotationSpeed() const { return m_RotationSpeed; }
		void SetZoomSensitivity(float sensitivity);
		inline float GetZoomSensitivity() const { return m_ZoomSensitivity; }

	protected:

		OrthographicCamera m_Camera;
		float m_AspectRatio = 1.0f;
		float m_ZoomLevel = 1.0f;
		float m_TranslationSpeed = 1.0f;
		float m_RotationSpeed = 10.0f;
		float m_ZoomSensitivity = 0.1f;

	private:

		bool OnMouseScrolled(MouseScrolledEvent& e);
	};

	// Fly

	class FlyCameraController : public CameraController {

	public:

		FlyCameraController(float field_of_view, float aspect_ratio, float near_plane, float far_plane);
		FlyCameraController() = default;

		virtual void OnUpdate(Time ts) override;
		virtual void OnEvent(Event& e) override;
		virtual void OnResize(float width, float height) override;

		inline const FlyCamera& GetCamera() const { return m_Camera; }
		inline sb::Matrix4f GetViewProjectionMatrix() { return m_Camera.GetProjectionMatrix() * m_Camera.GetViewMatrix(); }

		void SetSpeed(float speed);
		inline float GetSpeed() const { return m_Speed; }
		void SetSensitivity(float sensitivity);
		inline float GetSensitivity() const { return m_Sensitivity; }
		void SetCameraMovementDisabled(bool disable);

	protected:

		FlyCamera m_Camera;
		float m_Speed = 10.0f;
		float m_Sensitivity = 0.1f;
		bool m_Disabled = false;

	private:

		bool OnMouseMoved(MouseMovedEvent& e);

		bool m_FirstMouse = true;
		float m_LastXPos = 0.0f;
		float m_LastYPos = 0.0f;
	};

	// Editor

	class EditorCameraController : public CameraController {

	public:

		EditorCameraController(float field_of_view, float near_plane, float far_plane);
		EditorCameraController() = default;

		virtual void OnUpdate(Time ts) override;
		virtual void OnEvent(Event& e) override;
		virtual void OnResize(float width, float height) override;

		inline const EditorCamera& GetCamera() const { return m_Camera; }
		inline sb::Matrix4f GetViewProjectionMatrix() { return m_Camera.GetProjectionMatrix() * m_Camera.GetViewMatrix(); }

	protected:

		void MousePan(const Vector2f& delta);
		void MouseRotate(const Vector2f& delta);
		void MouseZoom(float delta);

		Vector2f GetPanSpeed() const;
		float GetRotationSpeed() const;
		float GetZoomSpeed() const;

		EditorCamera m_Camera;
		bool m_UpdateViewInit = true;
		Vector2f m_InitialMousePosition = { 0.0f, 0.0f };

	private:

		bool OnMouseScroll(MouseScrolledEvent& e);
	};
}
