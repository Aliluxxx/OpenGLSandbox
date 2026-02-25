#include "Core/Renderer/OpenGLDebuggerCallback.h"

#include "Core/Renderer/Context.h"
#include "Core/Base/Window.h"

namespace sb {

	Context::Context(const ContextSpecification& spec)
		: m_Specification(spec)
	{}

	void Context::Init() {

		SB_TRACE("Context initialization");

		glfwSetFramebufferSizeCallback(reinterpret_cast<GLFWwindow*>(m_Specification.Window->GetNativeWindow()), [](GLFWwindow* window, int width, int height) {

			glViewport(0, 0, width, height);
		});

		glfwMakeContextCurrent(reinterpret_cast<GLFWwindow*>(m_Specification.Window->GetNativeWindow()));

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			SB_ASSERT(false, "Failed to load GLAD");

#ifndef SB_PLATFORM_MACOSX
		if (m_Specification.EnableDebug) {

			int flags;
			glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
			if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {

				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageCallback(OpenGLDebuggerCallback, nullptr);
				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
			}
		}
#endif

		glfwSwapInterval(0);
	}

	void Context::Destroy() {

		SB_TRACE("Context deinitialization");
	}

	void Context::BeginFrame() {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	}

	void Context::EndFrame() {

		glfwSwapBuffers(reinterpret_cast<GLFWwindow*>(m_Specification.Window->GetNativeWindow()));
	}

	Ref<Context> Context::Create(const ContextSpecification& spec) {

		return CreateRef<Context>(spec);
	}
}
