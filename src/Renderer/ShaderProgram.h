#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <string>

namespace RenderEngine {
	class ShaderProgram {
	private:
		bool m_isCompiled;
		GLuint m_ID;
		bool createShader(const std::string &shader, const GLenum shaderType, GLuint &shaderID) noexcept;
		ShaderProgram() noexcept = delete;
		ShaderProgram(const ShaderProgram&) noexcept = delete;
		ShaderProgram &operator=(const ShaderProgram &) noexcept = delete; 
		ShaderProgram(ShaderProgram &&shaderProgram) noexcept;
		ShaderProgram &operator=(ShaderProgram &&shaderProgram) noexcept; 

	public:
		ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader) noexcept;
		~ShaderProgram() noexcept;
		bool isCompiled() const noexcept;
		void use() const noexcept;
		void setInt(const std::string &name, const GLint value) noexcept;
		void setFloat(const std::string &name, const GLfloat value) noexcept;
		void setMatrix4(const std::string &name, const glm::mat4 &matr) noexcept;
	};
}