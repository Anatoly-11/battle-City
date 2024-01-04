#ifndef _EAGLE_H
#define _EAGLE_H 1.0

#include <memory>
#include <array>
#include "IGameObject.h"
#include <glm/vec2.hpp>

namespace RendererEngine
{
  class Sprite;
}

class Eagle : public IGameObject {
public:
  enum class EEagleState : uint8_t {
    Alive = 0,
    Dead
  };
  Eagle(const glm::vec2 &position, const glm::vec2 &size, const float rotation) noexcept;
  virtual void render() const noexcept override;
  virtual void update(const uint64_t delta) noexcept override;
private:
  std::array<std::shared_ptr<RendererEngine::Sprite>, 2> m_sprites;
  EEagleState m_eCurrentEagleState;
};
#endif // !_EAGLE_H