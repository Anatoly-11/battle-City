#ifndef _BRICKWALL_H
#define _BRICKWALL_H 1.0

#include <memory>
#include <array>
#include "IGameObject.h"
#include <glm/vec2.hpp>

namespace RendererEngine
{
  class Sprite;
}

class BrickWall : public IGameObject {
public:
  enum class EBrickWallType {
    All,
    Top,
    Bottom,
    Left,
    Right,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
  };

  enum class EBrickState {
    All = 0,
    TopLeft,
    TopRight,
    Top,
    BottomLeft,
    Left,
    TopRight_BottomLeft,
    Top_BottomLeft,
    BottomRight,
    TopLeft_BottomRight,
    Right,
    Top_BottomRight,
    Bottom,
    TopLeft_Bottom,
    TopRight_Bottom,
    Destroyed
  };

  enum class EBrickLocation {
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
  };

  BrickWall(const EBrickWallType eBrickWallType, const glm::vec2 &position, const glm::vec2 &size, const float rotation) noexcept;
  virtual void render() const noexcept override;
  virtual void update(const uint64_t delta) noexcept override;
private:
  void renderBrick(const EBrickLocation eBrickLocation) const noexcept;
  std::array<EBrickState, 4> m_eCurrentBrickState;
  std::array<std::shared_ptr<RendererEngine::Sprite>, 15> m_sprites;
  std::array<glm::vec2, 4> m_blockOffsets;
};
#endif // !_BRICKWALL_H