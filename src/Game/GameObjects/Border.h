#pragma once

#include <memory>
#include <array>
#include "IGameObject.h"
#include <glm/vec2.hpp>

namespace RenderEngine
{
  class Sprite;
}

class Border : public IGameObject {
public:

  Border(const glm::vec2 &position, const glm::vec2 &size, const float rotation, const float layer) noexcept;
  virtual void render() const noexcept override;
private:
  std::shared_ptr<RenderEngine::Sprite> m_sprite;
};