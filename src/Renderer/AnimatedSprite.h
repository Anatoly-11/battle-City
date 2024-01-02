#ifndef _ANIMATEDSPRITE_H
#define _ANIMATEDSPRITE_H 1.0

#include "Sprite.h"
#include <map>
#include <vector>

namespace RendererEngine {
  class AnimatedSprite : public Sprite {
  public:
    AnimatedSprite(const std::shared_ptr<Texture2D> &pTexture, const std::string &initialSubTexture,
      const std::shared_ptr<ShaderProgram> &pShaderProgram) noexcept;
     
    virtual void render(const glm::vec2 &position, const glm::vec2 &size, const float rotation) const noexcept override;

    void update(const uint64_t delta) noexcept;
    
    void insertState(const std::string &state, const std::vector<std::pair<std::string,
      uint64_t>> &subTextureDuration) noexcept;

    void setState(const std::string &newState) noexcept;


  private:
    std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> m_statesMap;
    size_t m_currentFrame;
    uint64_t m_currentAnimationTime;
    std::map<std::string, std::vector<std::pair<std::string,
      uint64_t>>>::const_iterator m_pCurrentAnimationDurations;
    mutable bool m_dirty;
  };
}
#endif // !_ANIMATEDSPRITE_H