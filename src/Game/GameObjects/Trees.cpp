#include "Trees.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Trees::Trees(const glm::vec2 &position,
  const glm::vec2 &size, const float rotation, const float layer) noexcept : IGameObject(position, size, rotation, layer),
  m_sprite(ResourceManager::getSprite("trees")),
  m_blockOffsets{glm::vec2(0, size.y / 2),
                 glm::vec2(size.x / 2, size.y / 2),
                 glm::vec2(0, 0),
                 glm::vec2(size.y / 2, 0)} {
}

void Trees::renderBlock(const EBlockLocation eBlockLocation) const noexcept {
  m_sprite->render(m_position + m_blockOffsets[(size_t)eBlockLocation], m_size / 2.f, m_rotation, m_layer);
}

void Trees::render() const noexcept {
  renderBlock(EBlockLocation::BottomLeft);
  renderBlock(EBlockLocation::BottomRight);
  renderBlock(EBlockLocation::TopRight);
  renderBlock(EBlockLocation::TopLeft);
}