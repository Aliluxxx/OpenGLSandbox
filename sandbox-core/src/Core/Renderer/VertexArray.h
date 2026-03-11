#pragma once

#ifndef SB_PRECOMPILED_HEADER
#include <vector>
#include <glad/glad.h>
#endif

#include "Core/Base/Base.h"
#include "Core/Renderer/Buffer.h"

namespace sb {

	class VertexArray {

	public:

		VertexArray();
		~VertexArray();

		inline const GLuint& GetRendererID() const { return m_RendererID; }
		void AddVertexBuffer(const Ref<VertexBuffer>& buffer);
		inline const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		void SetIndexBuffer(const Ref<IndexBuffer>& buffer);
		inline const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

		static Ref<VertexArray> Create();

	private:

		GLuint m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}
