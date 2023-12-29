#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H 1.0

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <string>
#include <map>

namespace RendererEngine {
  class Texture2D {
  public:

    struct SubTexture2D {
      glm::vec2 leftBottomUV;
      glm::vec2 rightTopUV;

      SubTexture2D(const glm::vec2 &_leftBottomUV, const glm::vec2 &_rightTopUV) noexcept;
      SubTexture2D() noexcept;
    };

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
    unsigned int width() const noexcept;
    unsigned int height() const noexcept;
    void addSubTexture(const std::string &name, const glm::vec2 &_leftBottomUV, const glm::vec2 &_rightTopUV) noexcept;
    const SubTexture2D& getSubTexture(const std::string &name) const noexcept;
  private:
    GLuint m_ID;
    unsigned int m_width;
    unsigned int m_height;
    GLenum m_mode;
    std::map<std::string, SubTexture2D> m_subTextures;
  };
}
#endif // !_TEXTURE2D_H