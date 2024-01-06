#include "SpriteAnimator.h"
#include "Sprite.h"

namespace RenderEngine {
  SpriteAnimator::SpriteAnimator(std::shared_ptr<Sprite> pSprite) noexcept :
    m_pSprite(std::move(pSprite)),
    m_currentFrame(0),
    m_currentFrameDuration(m_pSprite->getFrameDuration(0)),
    m_currentAnimationTime(0), m_totalDuration(0) {
    for(size_t currentFrameId = 0; currentFrameId < m_pSprite->getFramesCount(); ++currentFrameId) {
      m_totalDuration += m_pSprite->getFrameDuration(currentFrameId);
    }
  }

  size_t SpriteAnimator::getCurrentFrame() const noexcept {
    return m_currentFrame;
  }

  void SpriteAnimator::update(const double delta) noexcept {
    m_currentAnimationTime += delta;
    while(m_currentAnimationTime >= m_currentFrameDuration) {
      m_currentAnimationTime -= m_currentFrameDuration;
      ++m_currentFrame;
      if(m_currentFrame == m_pSprite->getFramesCount()) {
        m_currentFrame = 0;
      }
    }
  }

  void SpriteAnimator::reset() noexcept {
    m_currentFrame = 0;
    m_currentFrameDuration = m_pSprite->getFrameDuration(0);
    m_currentAnimationTime = 0;
  }

  double SpriteAnimator::getTotalDuration() const noexcept {
    return m_totalDuration;
  }
}