#include "SpriteAnimator.h"
#include "Sprite.h"

namespace RendererEngine {
  SpriteAnimator::SpriteAnimator(std::shared_ptr<Sprite> pSprite) noexcept : 
    m_pSprite(std::move(pSprite)),
    m_currentFrame(0),
    m_currentFrameDuration(m_pSprite->getFrameDuration(0)),
    m_currentAnimationTime(0) {
  }

  size_t SpriteAnimator::getCurrentFrame() const noexcept {
    return m_currentFrame;
  }

  void SpriteAnimator::update(const uint64_t delta) noexcept {
    m_currentAnimationTime += delta;
    while(m_currentAnimationTime >= m_currentFrameDuration) {
      m_currentAnimationTime -= m_currentFrameDuration;
      ++m_currentFrame;
      if(m_currentFrame == m_pSprite->getFramesCount()) {
        m_currentFrame = 0;
      }
    }
  }
}