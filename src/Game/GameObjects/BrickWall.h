#ifndef _BRICKWALL_H
#define  _BRICKWALL_H 1.0

#include "IGameObject.h"
#include <memory>
#include <glm/vec2.hpp>

namespace RendererEngine {
  class Sprite;
}

class BrickWall : public IGameObject {
public:
  BrickWall(const std::shared_ptr<RendererEngine::Sprite> &pSprite, const glm::vec2 &position,
    const glm::vec2 &size, const float rotation) noexcept;
  virtual void render() const noexcept override;
  virtual void update(const uint64_t delta) noexcept override;
private:
  std::shared_ptr<RendererEngine::Sprite> m_pCurrentSprite;
};
#endif // !_BRICKWALL_H