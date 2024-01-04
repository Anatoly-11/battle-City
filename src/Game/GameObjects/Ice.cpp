#include "Ice.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Ice::Ice(const glm::vec2 &position,
  const glm::vec2 &size, const float rotation) noexcept : IGameObject(position, size, rotation),
  m_sprite(ResourceManager::getSprite("ice")),
  m_blockOffsets{glm::vec2(0, size.y / 2),
                 glm::vec2(size.x / 2, size.y / 2),
                 glm::vec2(0, 0),
                 glm::vec2(size.y / 2, 0)} {
}

void Ice::renderBlock(const EBlockLocation eBlockLocation) const noexcept {
  m_sprite->render(m_position + m_blockOffsets[(size_t)eBlockLocation], m_size / 2.f, m_rotation);
}

void Ice::render() const noexcept {
  renderBlock(EBlockLocation::BottomLeft);
  renderBlock(EBlockLocation::BottomRight);
  renderBlock(EBlockLocation::TopRight);
  renderBlock(EBlockLocation::TopLeft);
}