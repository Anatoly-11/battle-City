#include "Texture2D.h"
//-------------------------------------------------------------------------------------------------------------
namespace Renderer {
  Texture2D :: Texture2D(const GLuint width, const GLuint height, const unsigned char *data, 
    const unsigned int channels, const GLenum filter, const GLenum wrapMode) noexcept : m_width(width),
    m_height(height) {
    switch(channels) {
    case 4:
      m_mode = GL_RGBA;
      break;
    case 3:
      m_mode = GL_RGB;
      break;
    default:
      m_mode = GL_RGBA;
      break;
    }
    glGenTextures(1, &m_ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
  }
  //-----------------------------------------------------------------------------------------------------------
  Texture2D :: ~Texture2D() noexcept {
    glDeleteTextures(1, &m_ID);
  }
  //-----------------------------------------------------------------------------------------------------------
  Texture2D :: Texture2D(Texture2D &&texture) noexcept {
    m_ID = texture.m_ID; texture.m_ID = 0;
    m_mode = texture.m_mode;
    m_width = texture.m_width;
    m_height = texture.m_height;
  }
  //-----------------------------------------------------------------------------------------------------------
  Texture2D &Texture2D :: operator=(Texture2D &&texture) noexcept {
    glDeleteTextures(1, &m_ID);
    m_ID = texture.m_ID; texture.m_ID = 0;
    m_mode = texture.m_mode;
    m_width = texture.m_width;
    m_height = texture.m_height;
    return *this;
  }
  //-----------------------------------------------------------------------------------------------------------
  void Texture2D :: bind() const noexcept { 
    glBindTexture(GL_TEXTURE_2D, m_ID);
  }
  //-----------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------------