#ifndef _SPRITE_H
#define _SPRITE_H 1.0

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <string>
#include <memory>
#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

namespace RenderEngine
{
  class Texture2D;
  class ShaderProgram;
  class Sprite
  {
    Sprite(const Sprite&) = delete;
    Sprite &operator=(const Sprite&) = delete;
  public:

    struct FrameDescription
    {
      FrameDescription(const glm::vec2 _leftBottomUV, const glm::vec2 _rightTopUV, const double _duration) noexcept;
      glm::vec2 leftBottomUV;
      glm::vec2 rightTopUV;
      double duration;
    };

    Sprite(const std::shared_ptr<Texture2D> &pTexture,
      const std::string &initialSubTexture,
      const std::shared_ptr<ShaderProgram> &pShaderProgram) noexcept;

    ~Sprite() noexcept;

    void render(const glm::vec2 &position, const glm::vec2 &size, const float rotation, const float layer = 0.f,
      const size_t frameId = 0) const noexcept;

    double getFrameDuration(const size_t frameId) const noexcept;

    size_t getFramesCount() const noexcept;

    void insertFrames(std::vector<FrameDescription> framesDescriptions) noexcept;
  protected:
    std::shared_ptr<Texture2D> m_pTexture;
    std::shared_ptr<ShaderProgram> m_pShaderProgram;

    VertexArray m_vertexArray;
    VertexBuffer m_vertexCoordsBuffer;
    mutable VertexBuffer m_textureCoordsBuffer;
    IndexBuffer m_idexBuffer;
    std::vector<FrameDescription> m_framesDescriptions;
    mutable size_t lastFrameId;
  };
}
#endif // !_SPRITE_H
