#pragma once

#include <memory>
#include <array>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

#include <glm/vec2.hpp>

namespace RenderEngine
{
  class Sprite;
  class Sprite;
}

class Water : public IGameObject {
public:
  enum class EBlockLocation : uint8_t {
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
  };

  Water(const glm::vec2 &position, const glm::vec2 &size, const float rotation, const float layer) noexcept;
  void render() const noexcept override;
  void update(const double delta) noexcept override;
  virtual bool collides(const IGameObject::EObjectType objectType) const noexcept override;

private:
  void renderBlock(const EBlockLocation eBlockLocation) const noexcept;
  std::shared_ptr<RenderEngine::Sprite> m_sprite;
  RenderEngine::SpriteAnimator m_spriteAnimator;
  std::array<glm::vec2, 4> m_blockOffsets;
};