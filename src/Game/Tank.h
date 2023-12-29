#ifndef _TANK_H
#define _TANK_H 1.0

#include <memory>
#include <glm/vec2.hpp>

namespace RendererEngine{
  class AnimatedSprite;
}

class Tank {
public:
  enum class EOrientation{
    Top, Bottom,  Left, Right
  };

  Tank(const std::shared_ptr<RendererEngine::AnimatedSprite> pSprite, const float velocity, const glm::vec2 &position) noexcept;

  void render() const noexcept;

  void setOrientation(const EOrientation eOrientation) noexcept;

  void move(const bool move) noexcept;

  bool getmove() const noexcept;

  void update(const uint64_t delta) noexcept;
private:
  EOrientation m_eOrientation;
  const std::shared_ptr<RendererEngine::AnimatedSprite> m_pSprite;
  bool m_move;
  float m_velocity;
  glm::vec2 m_position;
  glm::vec2 m_moveOffset;
};

#endif //  _TANK_H