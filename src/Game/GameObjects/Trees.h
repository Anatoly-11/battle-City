#ifndef _TREES_H
#define _TREES_H 1.0

#include <memory>
#include <array>
#include "IGameObject.h"
#include <glm/vec2.hpp>

namespace RendererEngine
{
  class Sprite;
}

class Trees : public IGameObject {
public:
  enum class EBlockLocation : uint8_t {
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
  };

  Trees(const glm::vec2 &position, const glm::vec2 &size, const float rotation, const float layer) noexcept;
  virtual void render() const noexcept override;
private:
  void renderBlock(const EBlockLocation eBlockLocation) const noexcept;
  std::shared_ptr<RendererEngine::Sprite> m_sprite;
  std::array<glm::vec2, 4> m_blockOffsets;
};
#endif // !_TREES_H