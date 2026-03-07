#pragma once

#ifndef SB_PRECOMPILED_HEADER
#include <vector>
#include <glad/glad.h>
#endif

#include "Core/Base/Base.h"
#include "Core/Renderer/Buffer.h"
#include "Core/Renderer/VertexArray.h"

namespace sb {

	struct Vertex {

		sb::Vector3f Position;
		sb::Vector4f Color;
		sb::Vector3f Normal;
		sb::Vector2f TexCoords;
		sb::Vector3f Tangent;
		sb::Vector3f Bitangent;
	};

	class Mesh {

	public:

		Mesh(std::vector<Vertex>& vertices, std::vector<Uint32>& indices, const Matrix4f& transform = Matrix4f(1.0f));
		Mesh(const Mesh& other);
		Mesh(Mesh&& other) noexcept;
		Mesh& operator=(const Mesh& other);

		static Ref<Mesh> Create(std::vector<Vertex>& vertices, std::vector<Uint32>& indices, const Matrix4f& transform);

		inline const Ref<VertexArray>& GetVertexArray() const { return m_VAO; }
		inline Uint32 GetIndexCount() const { return m_VAO->GetIndexBuffer()->GetCount(); }
		inline const Matrix4f& GetTransformMatrix() const { return m_Transform; }

	private:

		void SetupBuffers();

		std::vector<Vertex> m_Vertices;
		std::vector<Uint32> m_Indices;
		Matrix4f m_Transform;
		Ref<VertexArray> m_VAO;
	};
}
