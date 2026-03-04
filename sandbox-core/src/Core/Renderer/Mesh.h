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
		sb::Vector3f Normals;
		sb::Vector2f TexCoords;
		sb::Vector2f Tangent;
	};

	class Mesh {

	public:

		Mesh(std::vector<Vertex>& vertices, std::vector<Uint32>& indices, GLenum primitive = GL_TRIANGLES);
		Mesh(const Mesh& other);
		Mesh(Mesh&& other) noexcept;
		Mesh& operator=(const Mesh& other);

		static Ref<Mesh> Create(std::vector<Vertex>& vertices, std::vector<Uint32>& indices, GLenum primitive = GL_TRIANGLES);

		inline const Ref<VertexArray>& GetVertexArray() const { return m_VAO; }
		inline const GLenum& GetPrimitive() const { return m_Primitive; }
		inline Uint32 GetIndexCount() const { return m_VAO->GetIndexBuffer()->GetCount(); }

	private:

		void SetupBuffers();

		std::vector<Vertex> m_Vertices;
		std::vector<Uint32> m_Indices;
		GLenum m_Primitive;
		Ref<VertexArray> m_VAO;
	};
}
