#include "Eagle.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

Eagle::Eagle(const glm::vec2 &position, const glm::vec2 &size, const float rotation,
  const float layer) noexcept : IGameObject(position, size, rotation, layer),
  m_sprites{ResourceManager::getSprite("eagle"), ResourceManager::getSprite("eagle_dead")},
  m_eCurrentEagleState(EEagleState::Alive) {
}

void Eagle::render() const noexcept {
  m_sprites[static_cast<size_t>(m_eCurrentEagleState)]->render(m_position, m_size, m_rotation, m_layer);
}

void Eagle::update(const double delta) noexcept {

}