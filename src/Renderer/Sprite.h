#pragma once
#ifndef _SPRITE_H
#define _SPRITE_H 1.0
//-------------------------------------------------------------------------------------------------------------
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <memory>
//-------------------------------------------------------------------------------------------------------------
namespace Renderer {
  class Texture2D;
  class ShaderProgram;
  class Sprite {
    Sprite(const Sprite&) = delete;
    Sprite &operator=(const Sprite&) = delete;
    std::shared_ptr<Texture2D> m_pTexture;
    std::shared_ptr<ShaderProgram> m_pShaderProgram;
    glm::vec2 m_position;
    glm::vec2 m_size;
    float m_rotation;
    GLuint m_VAO;
    GLuint m_vertexCoordsVBO;
    GLuint m_textureCoordsVBO;
  public:
    Sprite(const std::shared_ptr<Texture2D> pTexture, const std::shared_ptr<ShaderProgram> pShaderProgram,
      const glm::vec2 &position = glm::vec2(0.f), const glm::vec2 &size = glm::vec2(1.f), const float rotation = 0.f) noexcept;
    ~Sprite() noexcept;
    void render() noexcept;  
    void setPosition(const glm::vec2 &position) noexcept;  
    void setSize(const glm::vec2 &size) noexcept;  
    void setRotation(const float rotation) noexcept;  
  };
}
//-------------------------------------------------------------------------------------------------------------
#endif // !_SPRITE_H
//-------------------------------------------------------------------------------------------------------------