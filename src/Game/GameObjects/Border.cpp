#include "Border.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Border::Border(const glm::vec2 &position,
  const glm::vec2 &size, const float rotation, const float layer) noexcept : IGameObject(position, size, rotation, layer),
  m_sprite(ResourceManager::getSprite("border")) {
}

void Border::render() const noexcept {
  m_sprite->render(m_position,  m_size, m_rotation, m_layer);
}