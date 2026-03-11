#pragma once

#ifndef SB_PRECOMPILED_HEADER
#include <string>
#include <vector>
#include <initializer_list>
#include <glad/glad.h>
#endif

#include "Core/Base/Base.h"

namespace sb {

	enum class ShaderDataType {

		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	struct BufferElement {

		std::string Name;
		ShaderDataType Type;
		Uint32 Size;
		std::size_t Offset;
		Uint32 Divisor;
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, Uint32 divisor = 0, bool normalized = false);

		Uint32 GetComponentCount() const {

			switch (Type) {

				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3;
				case ShaderDataType::Mat4:    return 4;
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
			}

			SB_ASSERT(false, "Unknown ShaderDataType!");

			return 0;
		}

		Uint32 GetVertexAttributeCount() const {

			switch (Type) {

				case ShaderDataType::Mat3: return 3;
				case ShaderDataType::Mat4: return 4;
			}

			return 1;
		}
	};

	class BufferLayout {

	public:

		BufferLayout() : m_Elements(), m_Index(0), m_Stride(0) {}

		BufferLayout(const std::initializer_list<BufferElement>& elements, Uint32 index = 0)
			: m_Elements(elements), m_Index(index), m_Stride(0)

		{

			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline const Uint32 GetIndex() const { return m_Index; }
		inline const Uint32 GetStride() const { return m_Stride; }
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:

		void CalculateOffsetAndStride() {

			Uint32 offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {

				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

		std::vector<BufferElement> m_Elements;
		Uint32 m_Index;
		Uint32 m_Stride;
	};

	class VertexBuffer {

	public:

		VertexBuffer(Uint32 size);
		VertexBuffer(const void* vertices, Uint32 size);
		~VertexBuffer();

		inline const GLuint& GetRendererID() const { return m_RendererID; }
		inline const BufferLayout& GetLayout() const { return m_BufferLayout; }
		void SetData(const void* vertices, Uint32 size_in_bytes, Uint32 offset = 0);
		void SetLayout(const BufferLayout& layout);

		static Ref<VertexBuffer> Create(Uint32 size_in_bytes);
		static Ref<VertexBuffer> Create(const void* vertices, Uint32 size_in_bytes);

	private:

		GLuint m_RendererID;
		BufferLayout m_BufferLayout;
	};

	class IndexBuffer {

	public:

		IndexBuffer(const Uint32* indices, Uint32 size);
		~IndexBuffer();

		inline const Uint32& GetCount() const { return m_Size; }
		inline const GLuint& GetRendererID() const { return m_RendererID; }

		static Ref<IndexBuffer> Create(const Uint32* indices, Uint32 size);

	private:

		GLuint m_RendererID;
		Uint32 m_Size;
	};
}
