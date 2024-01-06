#ifndef _TANK_H
#define _TANK_H 1.0

#include <memory>
#include <glm/vec2.hpp>
#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"
#include "../../System/Timer.h"

namespace RenderEngine{
  class Sprite;
}

class Bullet;

class Tank : public IGameObject {
public:
  enum class EOrientation{
    Top, Bottom,  Left, Right
  };

  Tank(const double maxVelocity, const glm::vec2 &position, const glm::vec2 &size, const float layer) noexcept;

  virtual void render() const noexcept override;

  void setOrientation(const EOrientation eOrientation) noexcept;

  virtual void update(const double delta) noexcept override;

  double getMaxVelocity() const noexcept;

  virtual void setVelocity(const double velocity) noexcept override;

  void fire() const noexcept;

private:
  EOrientation m_eOrientation;
  std::shared_ptr<Bullet> m_pCurrentBullet;
  std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
  std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
  std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
  std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;
  std::shared_ptr<RenderEngine::Sprite> m_pSprite_respawn;
  std::shared_ptr<RenderEngine::Sprite> m_pSprite_shield;

  RenderEngine::SpriteAnimator m_spriteAnimator_top;
  RenderEngine::SpriteAnimator m_spriteAnimator_bottom;
  RenderEngine::SpriteAnimator m_spriteAnimator_left;
  RenderEngine::SpriteAnimator m_spriteAnimator_right;
  RenderEngine::SpriteAnimator m_spriteAnimator_respawn;
  RenderEngine::SpriteAnimator m_spriteAnimator_shield;
  
  Timer m_respawnTimer;
  Timer m_shieldTimer;

  double m_maxVelocity;
  bool m_isSpawning;
  bool m_hasShield;

};

#endif //  _TANK_H