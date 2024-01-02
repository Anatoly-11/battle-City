#include "Tank.h"
#include "../../Renderer/AnimatedSprite.h"

Tank::Tank(const std::shared_ptr<RendererEngine::AnimatedSprite> pSprite, const float velocity,
  const glm::vec2 &position, const glm::vec2 &size) noexcept : IGameObject(position, size, 0.f),
  m_eOrientation(EOrientation::Top), m_pSprite(pSprite), m_move(false), m_velocity(velocity),
  m_position(position), m_moveOffset({0.f, 1.f}) {
}

void Tank::render() const noexcept {
  m_pSprite->render(m_position, m_size, m_rotation);
}

void Tank::setOrientation(const EOrientation eOrientation) noexcept {
  if(eOrientation != m_eOrientation) {
    m_eOrientation = eOrientation;
    switch(m_eOrientation) {
    case Tank::EOrientation::Top:
      m_pSprite->setState("tankTopState");
      m_moveOffset.x = 0.f;
      m_moveOffset.y = 1.f;
      break;
    case Tank::EOrientation::Bottom:
      m_pSprite->setState("tankBottomState");
      m_moveOffset.x = 0.f;
      m_moveOffset.y = -1.f;
      break;
    case Tank::EOrientation::Left:
      m_pSprite->setState("tankLeftState");
      m_moveOffset.x = -1.f;
      m_moveOffset.y = 0.f;
      break;
    case Tank::EOrientation::Right:
      m_pSprite->setState("tankRightState");
      m_moveOffset.x = 1.f;
      m_moveOffset.y = 0.f;
      break;
    default:
      break;
    }
  }
}

void Tank::move(const bool move) noexcept {
  m_move = move;
}

bool Tank::getmove() const noexcept {
  return m_move;
}

void Tank::update(const uint64_t delta) noexcept {
  if(m_move) {
    m_position += delta * m_velocity * m_moveOffset;
    m_pSprite->update(delta);
  }
}