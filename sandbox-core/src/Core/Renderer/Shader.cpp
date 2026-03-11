#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Renderer.h"
#include <glm/gtc/type_ptr.hpp>

namespace sb {

	static std::string ShaderTypeToString(const GLenum type) {

		switch (type) {

		case GL_VERTEX_SHADER:
			return "Vertex";

		case GL_FRAGMENT_SHADER:
			return "Fragment";

		case GL_GEOMETRY_SHADER:
			return "Geometry";
		}

		SB_ASSERT(false, "Unknown shader type");

		return "";
	}

	Shader::Shader(const std::filesystem::path& vertex_path, const std::filesystem::path& fragment_path) {

		GLint vertexShader = Compile(ReadFile(vertex_path), GL_VERTEX_SHADER);
		GLint fragmentShader = Compile(ReadFile(fragment_path), GL_FRAGMENT_SHADER);

		if (vertexShader != 0 && fragmentShader != 0)
			Link(vertexShader, fragmentShader);
	}

	Shader::~Shader() {

		if (m_RendererID != 0)
			glDeleteProgram(m_RendererID);
	}

	Ref<Shader> Shader::Create(const std::filesystem::path& vertex_path, const std::filesystem::path& fragment_path) {

		return CreateRef<Shader>(vertex_path, fragment_path);
	}

	void Shader::UploadUniformInt(const std::string& name, int value) {

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void Shader::UploadUniformFloat(const std::string& name, float value) {

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void Shader::UploadUniformFloat2(const std::string& name, const Vector2f& value) {

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void Shader::UploadUniformFloat3(const std::string& name, const Vector3f& value) {

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void Shader::UploadUniformFloat4(const std::string& name, const Vector4f& value) {

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void Shader::UploadUniformMat3(const std::string& name, const Matrix3f& matrix) {

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::UploadUniformMat4(const std::string& name, const Matrix4f& matrix) {

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	GLuint Shader::Compile(const std::string& shader_src, const GLenum type) {

		GLuint shader = glCreateShader(type);
		const GLchar* source = (const GLchar*)shader_src.c_str();

		glShaderSource(shader, 1, &source, 0);
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE) {

			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			SB_ERROR("{0} shader error: {1}", ShaderTypeToString(type), infoLog.data());

			return 0;
		}

		return shader;
	}

	void Shader::Link(const GLuint vertex_shader, const GLuint fragment_shader) {

		m_RendererID = glCreateProgram();

		glAttachShader(m_RendererID, vertex_shader);
		glAttachShader(m_RendererID, fragment_shader);

		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);

		if (isLinked == GL_FALSE) {

			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);

			SB_ERROR("Linking error: {0}", infoLog.data());
		}

		glDetachShader(m_RendererID, vertex_shader);
		glDetachShader(m_RendererID, fragment_shader);
	}

	std::string Shader::ReadFile(const std::filesystem::path& filepath) {

		std::string result;
		std::ifstream in(filepath, std::ios::in, std::ios::binary);

		if (in) {

			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}

		else
			SB_ERROR("Could not open file '{0}'", filepath.string());

		return result;
	}
}