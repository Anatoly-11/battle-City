#pragma once
#ifndef _ANIMATEDSPRITE_H
#define _ANIMATEDSPRITE_H 1.0

#include "Sprite.h"
#include <map>
#include <vector>

namespace Renderer {
  class AnimatedSprite : public Sprite {
  public:
    AnimatedSprite(const std::shared_ptr<Texture2D> &pTexture,
      const std::string &initialSubTexture,
      const std::shared_ptr<ShaderProgram> &pShaderProgram,
      const glm::vec2 &position = glm::vec2(0.f),
      const glm::vec2 &size = glm::vec2(1.f),
      const float rotation = 0.f) noexcept;

    virtual void render() const noexcept override;

    void update(const uint64_t delta) noexcept;
    
    void insertState(const std::string &state, const std::vector<std::pair<std::string, uint64_t>> &subTextureDuration) noexcept;

    void setState(const std::string &newState) noexcept;

    const std::string &getState() const noexcept;

  private:
    std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> m_statesMap;
    size_t m_currentFrame;
    uint64_t m_currentAnimationTime;
    std::map<std::string, std::vector<std::pair<std::string,
      uint64_t>>>::const_iterator m_pCurrentAnimationDurations;
    std::string m_currentStateName;
    mutable bool m_dirty;
  };
}
#endif // !_ANIMATEDSPRITE_H