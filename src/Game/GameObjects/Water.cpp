#include "Water.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Water::Water(const glm::vec2 &position,
  const glm::vec2 &size, const float rotation, const float layer) noexcept : IGameObject(position, size, rotation, layer),
  m_sprite(ResourceManager::getSprite("water")), m_spriteAnimator(m_sprite),
  m_blockOffsets{glm::vec2(0, size.y / 2),
                 glm::vec2(size.x / 2, size.y / 2),
                 glm::vec2(0, 0),
                 glm::vec2(size.y / 2, 0)} {
}

void Water::renderBlock(const EBlockLocation eBlockLocation) const noexcept {
  m_sprite->render(m_position + m_blockOffsets[(size_t)eBlockLocation], m_size / 2.f, m_rotation, m_layer,
    m_spriteAnimator.getCurrentFrame());
}

void Water::render() const noexcept {
  renderBlock(EBlockLocation::BottomLeft);
  renderBlock(EBlockLocation::BottomRight);
  renderBlock(EBlockLocation::TopRight);
  renderBlock(EBlockLocation::TopLeft);
}

void Water::update(const uint64_t delta) noexcept {
  m_spriteAnimator.update(delta);
}