#pragma once

#include <memory>
#include <array>
#include "IGameObject.h"
#include <glm/vec2.hpp>

namespace RenderEngine
{
  class Sprite;
}

class Ice : public IGameObject {
public:
  enum class EBlockLocation : uint8_t {
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
  };

  Ice(const glm::vec2 &position, const glm::vec2 &size, const float rotation, const float layer) noexcept;
  virtual void render() const noexcept override;
private:
  void renderBlock(const EBlockLocation eBlockLocation) const noexcept;
  std::shared_ptr<RenderEngine::Sprite> m_sprite;
  std::array<glm::vec2, 4> m_blockOffsets;
};