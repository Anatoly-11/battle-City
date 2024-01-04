#include "BetonWall.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

BetonWall::BetonWall(const EBetonWallType eBetonWallType, const glm::vec2 &position,
  const glm::vec2 &size, const float rotation, const float layer) noexcept : IGameObject(position, size, rotation, layer),
  m_eCurrentBlockState{ EBlockState::Destroyed,
                        EBlockState::Destroyed,
                        EBlockState::Destroyed,
                        EBlockState::Destroyed },
  m_sprite(ResourceManager::getSprite("betonWall")),
  m_blockOffsets{glm::vec2(0, size.y / 2),
                 glm::vec2(size.x / 2, size.y / 2),
                 glm::vec2(0, 0),
                 glm::vec2(size.y / 2, 0)} {
  switch(eBetonWallType) {
  case EBetonWallType::All:
    m_eCurrentBlockState.fill(EBlockState::Enabled);
    break;
  case EBetonWallType::Top:
    m_eCurrentBlockState[(size_t)EBlockLocation::TopLeft] =     EBlockState::Enabled;
    m_eCurrentBlockState[(size_t)EBlockLocation::TopRight] =    EBlockState::Enabled;
    break;                        
  case EBetonWallType::Bottom:    
    m_eCurrentBlockState[(size_t)EBlockLocation::BottomLeft] =  EBlockState::Enabled;
    m_eCurrentBlockState[(size_t)EBlockLocation::BottomRight] = EBlockState::Enabled;
    break;                        
  case EBetonWallType::Left:      
    m_eCurrentBlockState[(size_t)EBlockLocation::TopLeft] =     EBlockState::Enabled;
    m_eCurrentBlockState[(size_t)EBlockLocation::BottomLeft] =  EBlockState::Enabled;
    break;                        
  case EBetonWallType::Right:     
    m_eCurrentBlockState[(size_t)EBlockLocation::TopRight] =    EBlockState::Enabled;
    m_eCurrentBlockState[(size_t)EBlockLocation::BottomRight] = EBlockState::Enabled;
    break;                        
  case EBetonWallType::TopLeft:   
    m_eCurrentBlockState[(size_t)EBlockLocation::TopLeft] =     EBlockState::Enabled;
    break;                        
  case EBetonWallType::TopRight:  
    m_eCurrentBlockState[(size_t)EBlockLocation::TopRight] =    EBlockState::Enabled;
    break;                        
  case EBetonWallType::BottomLeft:
    m_eCurrentBlockState[(size_t)EBlockLocation::BottomLeft] =  EBlockState::Enabled;
    break;                        
  case EBetonWallType::BottomRight:
    m_eCurrentBlockState[(size_t)EBlockLocation::BottomRight] = EBlockState::Enabled;
    break;                        
  default:                        
    break;
  }
}

void BetonWall::renderBlock(const EBlockLocation eBlockLocation) const noexcept {
  const EBlockState state = m_eCurrentBlockState[(size_t)eBlockLocation];
  if(state != EBlockState::Destroyed) {
    m_sprite->render(m_position + m_blockOffsets[(size_t)eBlockLocation], m_size /2.f, m_rotation, m_layer);
  }
}

void BetonWall::render() const noexcept {
  renderBlock(EBlockLocation::BottomLeft);
  renderBlock(EBlockLocation::BottomRight);
  renderBlock(EBlockLocation::TopRight);
  renderBlock(EBlockLocation::TopLeft);
}

void BetonWall::update(const uint64_t delta) noexcept {
}