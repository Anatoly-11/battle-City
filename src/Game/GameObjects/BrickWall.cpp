#include "BrickWall.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

BrickWall::BrickWall(const EBrickWallType eBrickWallType, const glm::vec2 &position,
  const glm::vec2 &size, const float rotation, const float layer) noexcept : IGameObject(position, size, rotation, layer),
  m_eCurrentBrickState{ EBrickState::Destroyed,
                        EBrickState::Destroyed,
                        EBrickState::Destroyed,
                        EBrickState::Destroyed },
  m_sprites{ ResourceManager::getSprite("brickWall_All"),
             ResourceManager::getSprite("brickWall_TopLeft"),
             ResourceManager::getSprite("brickWall_TopRight"),
             ResourceManager::getSprite("brickWall_Top"),
             ResourceManager::getSprite("brickWall_BottomLeft"),
             ResourceManager::getSprite("brickWall_Left"),
             ResourceManager::getSprite("brickWall_TopRight_BottomLeft"),
             ResourceManager::getSprite("brickWall_Top_BottomLeft"),
             ResourceManager::getSprite("brickWall_BottomRight"),
             ResourceManager::getSprite("brickWall_TopLeft_BottomRight"),
             ResourceManager::getSprite("brickWall_Right"),
             ResourceManager::getSprite("brickWall_Top_BottomRight"),
             ResourceManager::getSprite("brickWall_Bottom"),
             ResourceManager::getSprite("brickWall_TopLeft_Bottom"),
             ResourceManager::getSprite("brickWall_TopRight_Bottom") },
  m_blockOffsets{glm::vec2(0, size.y / 2),
  glm::vec2(size.x / 2, size.y / 2),
  glm::vec2(0, 0),
  glm::vec2(size.y / 2, 0)} {
  switch(eBrickWallType) {
  case EBrickWallType::All:
    m_eCurrentBrickState.fill(EBrickState::All);
    break;
  case EBrickWallType::Top:
    m_eCurrentBrickState[(size_t)EBrickLocation::TopLeft] =     EBrickState::All;
    m_eCurrentBrickState[(size_t)EBrickLocation::TopRight] =    EBrickState::All;
    break;
  case EBrickWallType::Bottom:
    m_eCurrentBrickState[(size_t)EBrickLocation::BottomLeft] =  EBrickState::All;
    m_eCurrentBrickState[(size_t)EBrickLocation::BottomRight] = EBrickState::All;
    break;
  case EBrickWallType::Left:
    m_eCurrentBrickState[(size_t)EBrickLocation::TopLeft] =     EBrickState::All;
    m_eCurrentBrickState[(size_t)EBrickLocation::BottomLeft] =  EBrickState::All;
    break;
  case EBrickWallType::Right:
    m_eCurrentBrickState[(size_t)EBrickLocation::TopRight] =    EBrickState::All;
    m_eCurrentBrickState[(size_t)EBrickLocation::BottomRight] = EBrickState::All;
    break;
  case EBrickWallType::TopLeft:
    m_eCurrentBrickState[(size_t)EBrickLocation::TopLeft] =     EBrickState::All;
    break;
  case EBrickWallType::TopRight:
    m_eCurrentBrickState[(size_t)EBrickLocation::TopRight] =    EBrickState::All;
    break;
  case EBrickWallType::BottomLeft:
    m_eCurrentBrickState[(size_t)EBrickLocation::BottomLeft] =  EBrickState::All;
    break;
  case EBrickWallType::BottomRight:
    m_eCurrentBrickState[(size_t)EBrickLocation::BottomRight] = EBrickState::All;
    break;
  default:
    break;
  }
}

void BrickWall::renderBrick(const EBrickLocation eBrickLocation) const noexcept {
  const EBrickState state = m_eCurrentBrickState[(size_t)eBrickLocation];
  if(state != EBrickState::Destroyed) {
    m_sprites[(size_t)state]->render(m_position + m_blockOffsets[(size_t)eBrickLocation], m_size /2.f, m_rotation, m_layer);
  }
}

void BrickWall::render() const noexcept {
  renderBrick(EBrickLocation::BottomLeft);
  renderBrick(EBrickLocation::BottomRight);
  renderBrick(EBrickLocation::TopRight);
  renderBrick(EBrickLocation::TopLeft);
}

void BrickWall::update(const uint64_t delta) noexcept {
}