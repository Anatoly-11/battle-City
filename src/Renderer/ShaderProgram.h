#pragma once
#ifndef _SHADERPROGRAM_H_
#define _SHADERPROGRAM_H_ 1.0
//-------------------------------------------------------------------------------------------------------------
#include <glad/glad.h>
#include <string>
//-------------------------------------------------------------------------------------------------------------
namespace Renderer {
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
	};
}
//-------------------------------------------------------------------------------------------------------------
#endif // !_SHADERPROGRAM_H_
//-------------------------------------------------------------------------------------------------------------
