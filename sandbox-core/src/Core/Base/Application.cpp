#include "Core/Base/Application.h"

namespace sb {

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& spec)
		: m_Specification(spec)

	{

		SB_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		WindowSpecification wSpec;
		wSpec.Title = spec.Name;

		m_Window = Window::Create(wSpec);
		m_Window->SetEventCallback(SB_BIND_EVENT_FN(Application::OnEvent));

		ContextSpecification cSpec;
		cSpec.WindowPtr = m_Window->GetNativeWindow();
		cSpec.AppName = m_Window->GetTitle();
		cSpec.EngineName = "OpenGL Core";
#ifndef SB_DIST
		cSpec.EnableDebug = true;
#endif
		Ref<Context> context = Context::Create(cSpec);
		m_Window->SetContext(context);
		m_Window->GetContext()->Init();

		Renderer::Init(context);
	}

	Application::~Application() {

		m_LayerStack.Clear();
		m_Window->GetContext()->Destroy();
		Renderer::Shutdown();
	}

	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SB_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SB_BIND_EVENT_FN(Application::OnWindowResized));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {

			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Ref<Layer> layer) {

		s_Instance->m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Ref<Layer> overlay) {

		s_Instance->m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Close() {

		s_Instance->m_Running = false;
	}

	void Application::Run() {

		while (m_Running) {

			float time = m_Timer.GetElapsedTime().AsSeconds();
			Time timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_Window->OnUpdate();

			if (m_Minimized)
				continue;

			m_Window->BeginFrame();

			for (Ref<Layer> layer : m_LayerStack)
				layer->OnUpdate(timestep);

			for (Ref<Layer> layer : m_LayerStack)
				layer->OnImGuiRender();

			m_Window->EndFrame();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {

		m_Running = false;
		return false;
	}

	bool Application::OnWindowResized(WindowResizeEvent& e) {

		if (e.GetWidth() == 0 || e.GetHeight() == 0) {

			m_Minimized = true;
			return false;
		}

		else {

			m_Minimized = false;
		}

		return false;
	}

	const char* ApplicationCommandLineArgs::operator[](int index) const {

		SB_ASSERT(index < Count, "Array index out of bounds");
		return Args[index];
	}
}
