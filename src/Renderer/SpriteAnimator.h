#ifndef _SPRITEANIMATOR_H
#define _SPRITEANIMATOR_H 1.0

#include <memory>

namespace RendererEngine {
  class Sprite;
  class SpriteAnimator {
  public:
    SpriteAnimator(std::shared_ptr<Sprite> pSprite) noexcept;
    size_t getCurrentFrame() const noexcept;
    void update(const uint64_t delta) noexcept;
  private:
    std::shared_ptr<Sprite> m_pSprite;
    size_t m_currentFrame;
    uint64_t m_currentFrameDuration;
    uint64_t m_currentAnimationTime;
  };
}
#endif // !_SPRITEANIMATOR_H
