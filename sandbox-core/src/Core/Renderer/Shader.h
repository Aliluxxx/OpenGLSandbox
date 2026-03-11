#pragma once

#ifndef SB_PRECOMPILED_HEADER
#include <string>
#include <filesystem>
#include <glad/glad.h>
#endif

#include "Core/Base/Base.h"

namespace sb {

	class Shader {

	public:

		Shader(const std::filesystem::path& vertex_path, const std::filesystem::path& fragment_path);
		~Shader();

		static Ref<Shader> Create(const std::filesystem::path& vertex_path, const std::filesystem::path& fragment_path);

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const Vector2f& value);
		void UploadUniformFloat3(const std::string& name, const Vector3f& value);
		void UploadUniformFloat4(const std::string& name, const Vector4f& value);

		void UploadUniformMat3(const std::string& name, const Matrix3f& matrix);
		void UploadUniformMat4(const std::string& name, const Matrix4f& matrix);

		inline const GLuint& GetRendererID() const { return m_RendererID; }

	private:

		GLuint Compile(const std::string& shader_src, const GLenum type);
		void Link(const GLuint vertex_shader, const GLuint fragment_shader);
		std::string ReadFile(const std::filesystem::path& filepath);

		GLuint m_RendererID = 0;
	};
}