#ifndef _IGAMEOBJECT_H
#define _IGAMEOBJECT_H 1.0

#include <glm/vec2.hpp>

class IGameObject {
public:
  IGameObject(const glm::vec2 &position, const glm::vec2 &size, const float rotation) noexcept;
  virtual void render() const noexcept = 0;
  virtual void update(const uint64_t delta) noexcept = 0;
  virtual ~IGameObject() noexcept;
protected:
  glm::vec2 m_position;
  glm::vec2 m_size;
  float m_rotation;
};

#endif // !_IGAMEOBJECT_H