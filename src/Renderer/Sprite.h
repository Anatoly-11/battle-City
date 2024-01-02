#ifndef _SPRITE_H
#define _SPRITE_H 1.0

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <string>
#include <memory>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

namespace RendererEngine {
  class Texture2D;
  class ShaderProgram;
  class Sprite {
    Sprite(const Sprite&) = delete;
    Sprite &operator=(const Sprite&) = delete;
  protected:
    std::shared_ptr<Texture2D> m_pTexture;
    std::shared_ptr<ShaderProgram> m_pShaderProgram;

    VertexArray m_vertexArray;
    VertexBuffer m_vertexCoordsBuffer;
    VertexBuffer m_textureCoordsBuffer;
    IndexBuffer m_idexBuffer;

  public:
    Sprite(const std::shared_ptr<Texture2D> &pTexture,
      const std::string &initialSubTexture,
      const std::shared_ptr<ShaderProgram> &pShaderProgram) noexcept;
    ~Sprite() noexcept;
    virtual void render(const glm::vec2 &position, const glm::vec2 &size, const float rotation) const noexcept;
  };
}
#endif // !_SPRITE_H