#pragma once
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H 1.0
//-------------------------------------------------------------------------------------------------------------
#include <glad/glad.h>
#include <string>
//-------------------------------------------------------------------------------------------------------------
namespace Renderer {
  class Texture2D {
    GLuint m_ID;
    unsigned int m_width;
    unsigned int m_height;
    GLenum m_mode;
  public:
    Texture2D(const GLuint width, const GLuint height, const unsigned char *data,
      const unsigned int channels = 4, const GLenum filter = GL_LINEAR,
      const GLenum wrapMode = GL_CLAMP_TO_EDGE) noexcept;
    ~Texture2D() noexcept;
    Texture2D() = delete;
    Texture2D(const Texture2D&) = delete;
    Texture2D &operator=(Texture2D&) = delete;
    Texture2D(Texture2D &&texture) noexcept;
    Texture2D &operator=(Texture2D &&texture) noexcept;
    void bind() const noexcept;  
  };
}
//-------------------------------------------------------------------------------------------------------------
#endif // !_TEXTURE2D_H
//-------------------------------------------------------------------------------------------------------------