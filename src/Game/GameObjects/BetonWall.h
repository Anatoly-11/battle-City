#pragma once

#include <memory>
#include <array>
#include "IGameObject.h"
#include <glm/vec2.hpp>

namespace RenderEngine
{
  class Sprite;
}

class BetonWall : public IGameObject {
public:
  enum class EBetonWallType : uint8_t {
    All,
    Top,
    Bottom,
    Left,
    Right,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
  };

  enum class EBlockState : uint8_t {
    Enabled = 0,
    Destroyed
  };

  enum class EBlockLocation : uint8_t {
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
  };

  BetonWall(const EBetonWallType eBetonWallType, const glm::vec2 &position, const glm::vec2 &size, const float rotation,
    const float layer) noexcept;
  virtual void render() const noexcept override;
  virtual void update(const double delta) noexcept override;
private:
  void renderBlock(const EBlockLocation eBlockLocation) const noexcept;
  std::array<EBlockState, 4> m_eCurrentBlockState;
  std::shared_ptr<RenderEngine::Sprite> m_sprite;
  std::array<glm::vec2, 4> m_blockOffsets;
};