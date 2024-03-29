#pragma once

#include <glm/vec2.hpp>
#include "../../Physics/PhysicsEngine.h"

class IGameObject {
public:
  enum class EObjectType : uint8_t {
    BetonWall,
    Border,
    BrickWall,
    Bullet,
    Eagle,
    Ice,
    Tank,
    Trees,
    Water,
    Unknown
  };

  IGameObject(const EObjectType objectType, const glm::vec2 &position, const glm::vec2 &size, const float rotation,
    const float layer) noexcept;
  void setOwner(IGameObject *pOwner) noexcept;
  IGameObject *getOwner() const  noexcept;
  virtual void render() const noexcept = 0;
  virtual void update(const double delta) noexcept;
  virtual ~IGameObject() noexcept;
  virtual glm::vec2 &getCurrentPosition() noexcept;
  virtual glm::vec2 &getTargetPosition() noexcept;
  virtual glm::vec2 &getCurrentDirection() noexcept;
  virtual double getCurrentVelocity() const noexcept;
  virtual void setVelocity(const double velosity) noexcept;
  const glm::vec2 &getSize() const noexcept;
  const std::vector<Physics::Collider> &getColliders() const noexcept;
  EObjectType getObjectType() const noexcept;
  virtual bool collides(const EObjectType objectType) const noexcept;
  virtual void onCollision()  noexcept;
protected:
  IGameObject *m_pOwner;
  glm::vec2 m_position;
  glm::vec2 m_targetPosition;
  glm::vec2 m_size;
  float m_rotation;
  float m_layer;
  EObjectType m_eObjectType;

  glm::vec2 m_direction;
  double m_velocity;
  std::vector<Physics::Collider> m_colliders;
};