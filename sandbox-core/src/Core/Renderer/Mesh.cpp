#include "Core/Renderer/Mesh.h"

namespace sb {

	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<Uint32>& indices, const Matrix4f& transform)
		:
		m_Vertices(std::move(vertices)),
		m_Indices(std::move(indices)),
		m_Transform(transform)

	{

		SetupBuffers();
	}

	Mesh::Mesh(const Mesh& other)
		:
		m_Vertices(other.m_Vertices),
		m_Indices(other.m_Indices),
		m_Transform(other.m_Transform)

	{

		SetupBuffers();
	}

	Mesh::Mesh(Mesh&& other) noexcept
		:
		m_Vertices(std::move(other.m_Vertices)),
		m_Indices(std::move(other.m_Indices)),
		m_Transform(other.m_Transform),
		m_VAO(other.m_VAO)

	{

		other.m_VAO = nullptr;
	}

	Mesh& Mesh::operator=(const Mesh& other) {

		this->m_Vertices = other.m_Vertices;
		this->m_Indices = other.m_Indices;
		this->m_Transform = other.m_Transform;
		SetupBuffers();

		return *this;
	}

	Ref<Mesh> Mesh::Create(std::vector<Vertex>& vertices, std::vector<Uint32>& indices, const Matrix4f& transform) {

		return CreateRef<Mesh>(vertices, indices, transform);
	}

	void Mesh::SetupBuffers() {

		m_VAO = VertexArray::Create();

		Ref<VertexBuffer> VBO = VertexBuffer::Create(m_Vertices.data(), (Uint32)m_Vertices.size() * sizeof(Vertex));
		VBO->SetLayout({

			{ sb::ShaderDataType::Float3, "a_Position" },
			{ sb::ShaderDataType::Float4, "a_Color" },
			{ sb::ShaderDataType::Float3, "a_Normals" },
			{ sb::ShaderDataType::Float2, "a_TexCoords" },
			{ sb::ShaderDataType::Float3, "a_Tangent" },
			{ sb::ShaderDataType::Float3, "a_Bitangent" }
		});

		Ref<IndexBuffer> EBO = IndexBuffer::Create(m_Indices.data(), (Uint32)m_Indices.size());

		m_VAO->AddVertexBuffer(VBO);
		m_VAO->SetIndexBuffer(EBO);
	}
}
