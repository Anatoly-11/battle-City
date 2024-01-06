#ifndef _SPRITEANIMATOR_H
#define _SPRITEANIMATOR_H 1.0

#include <memory>

namespace RenderEngine {
  class Sprite;
  class SpriteAnimator {
  public:
    SpriteAnimator(std::shared_ptr<Sprite> pSprite) noexcept;
    size_t getCurrentFrame() const noexcept;
    void update(const double delta) noexcept;
    double getTotalDuration() const noexcept;
    void reset() noexcept;
  private:
    std::shared_ptr<Sprite> m_pSprite;
    size_t m_currentFrame;
    double m_currentFrameDuration;
    double m_currentAnimationTime;
    double m_totalDuration;
  };
}
#endif // !_SPRITEANIMATOR_H
