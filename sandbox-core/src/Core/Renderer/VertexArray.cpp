#include "Core/Renderer/VertexArray.h"

#include "Core/Renderer/Utils.h"

namespace sb {

	VertexArray::VertexArray() {

		glGenVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray() {

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& buffer) {

		SB_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		m_VertexBuffers.push_back(buffer);

		glBindVertexArray(m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, buffer->GetRendererID());
		Uint32 index = 0;
		const auto& layout = buffer->GetLayout();
		for (const auto& element : layout) {

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				Utils::ShaderDataTypeToOpenGLType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			index++;
		}
	}

	void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& buffer) {

		glBindVertexArray(m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->GetRendererID());
		m_IndexBuffer = buffer;
	}

	Ref<VertexArray> VertexArray::Create() {

		return CreateRef<VertexArray>();
	}
}
