#include "Core/Renderer/Utils.h"

#include "Core/Renderer/Buffer.h"

namespace sb {

	BufferElement::BufferElement(ShaderDataType type, const std::string& name, bool normalized)
		: Name(name), Type(type), Size(Utils::ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)

	{}

	VertexBuffer::VertexBuffer(Uint32 size_in_bytes) {

		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size_in_bytes, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(void* vertices, Uint32 size_in_bytes) {

		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size_in_bytes, vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer() {

		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::SetData(void* vertices, Uint32 size_in_bytes, Uint32 offset) {

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size_in_bytes, vertices);
	}

	void VertexBuffer::SetLayout(const BufferLayout& layout) {

		m_BufferLayout = layout;
	}

	Ref<VertexBuffer> VertexBuffer::Create(Uint32 size_in_bytes) {

		return CreateRef<VertexBuffer>(size_in_bytes);
	}

	Ref<VertexBuffer> VertexBuffer::Create(void* vertices, Uint32 size_in_bytes) {

		return CreateRef<VertexBuffer>(vertices, size_in_bytes);
	}

	IndexBuffer::IndexBuffer(Uint32* indices, Uint32 size)
		: m_Size(size)

	{

		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer() {

		glDeleteBuffers(1, &m_RendererID);
	}

	Ref<IndexBuffer> IndexBuffer::Create(Uint32* indices, Uint32 size) {

		return CreateRef<IndexBuffer>(indices, size);
	}
}
