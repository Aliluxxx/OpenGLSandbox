#pragma once

#ifndef SB_PRECOMPILED_HEADER
#include <glad/glad.h>
#endif

#include "Core/Renderer/Buffer.h"

namespace sb {

	namespace Utils {

		static Uint32 ShaderDataTypeSize(ShaderDataType type) {

			switch (type) {

				case ShaderDataType::Float:    return 4;
				case ShaderDataType::Float2:   return 4 * 2;
				case ShaderDataType::Float3:   return 4 * 3;
				case ShaderDataType::Float4:   return 4 * 4;
				case ShaderDataType::Mat3:     return 4 * 3 * 3;
				case ShaderDataType::Mat4:     return 4 * 4 * 4;
				case ShaderDataType::Int:      return 4;
				case ShaderDataType::Int2:     return 4 * 2;
				case ShaderDataType::Int3:     return 4 * 3;
				case ShaderDataType::Int4:     return 4 * 4;
				case ShaderDataType::Bool:     return 1;
			}

			SB_ASSERT(false, "Unknown ShaderDataType!");

			return 0;
		}

		static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type) {

			switch (type) {

				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
					return GL_FLOAT;
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
					return GL_INT;
			}

			SB_ASSERT(false, "Unknown ShaderDataType!");

			return 0;
		}
	}
}
