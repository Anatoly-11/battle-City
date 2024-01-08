#pragma once

#include <memory>
#include <array>
#include "IGameObject.h"
#include <glm/vec2.hpp>

namespace RenderEngine
{
  class Sprite;
}

class Eagle : public IGameObject {
public:
  enum class EEagleState : uint8_t {
    Alive = 0,
    Dead
  };
  Eagle(const glm::vec2 &position, const glm::vec2 &size, const float rotation, const float layer) noexcept;
  virtual void render() const noexcept override;
  virtual void update(const double delta) noexcept override;
private:
  std::array<std::shared_ptr<RenderEngine::Sprite>, 2> m_sprites;
  EEagleState m_eCurrentEagleState;
};