#include "Core/Renderer/Utils.h"

#include "Core/Renderer/Buffer.h"

namespace sb {

	BufferElement::BufferElement(ShaderDataType type, const std::string& name, bool normalized)
		: Name(name), Type(type), Size(Utils::ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)

	{}

	VertexBuffer::VertexBuffer(Uint32 size) {

		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(float* vertices, Uint32 size) {

		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer() {

		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::SetData(float* vertices, Uint32 size, Uint32 offset) {

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
	}

	void VertexBuffer::SetLayout(const BufferLayout& layout) {

		m_BufferLayout = layout;
	}

	IndexBuffer::IndexBuffer(Uint32* indices, Uint32 size) {

		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer() {

		glDeleteBuffers(1, &m_RendererID);
	}
}
