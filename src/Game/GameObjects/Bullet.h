#ifndef _BULLET_H
#define _BULLET_H 1.0

#include "IGameObject.h"

#include <array>
#include <memory>

namespace RendererEngine {
  class Sprite;
}

class Bullet : public IGameObject {
public:
  enum class EOrientation : uint8_t {
    Top,
    Bottom,
    Left,
    Right
  };

  Bullet(const double velocity, const glm::vec2 &position, const glm::vec2 &size, const float layer) noexcept;
  virtual void render() const noexcept override;
  bool isActive() const noexcept;
  void fire(const glm::vec2 &position, const glm::vec2 &direction) noexcept;
  virtual void onCollision() noexcept override;

private:
  std::shared_ptr<RendererEngine::Sprite> m_pSprite_top;
  std::shared_ptr<RendererEngine::Sprite> m_pSprite_bottom;
  std::shared_ptr<RendererEngine::Sprite> m_pSprite_left;
  std::shared_ptr<RendererEngine::Sprite> m_pSprite_right;

  EOrientation m_eOrientation;
  double m_maxVelocity;
  bool m_isActive;
};
#endif // !_BULLET_H