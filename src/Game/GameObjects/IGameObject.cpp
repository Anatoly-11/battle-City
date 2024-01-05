#include "IGameObject.h"

IGameObject::IGameObject(const glm::vec2 &position, const glm::vec2 &size, const float rotation, const float layer) noexcept :
  m_position(position),
  m_size(size),
  m_rotation(rotation),
  m_layer(layer),
  m_direction(0.f, 1.f),
  m_velocity(0.f) {
}

void IGameObject::update(const double delta) noexcept {
}


glm::vec2 &IGameObject::getCurrentPosition() noexcept{
  return m_position;
}

glm::vec2 &IGameObject::getCurrentDirection() noexcept {
  return m_direction;
}

double IGameObject::getCurrentVelocity() const noexcept {
  return m_velocity;
}

void IGameObject::setVelocity(const double velosity) noexcept {
  m_velocity = velosity;
}

IGameObject::~IGameObject() noexcept {
}