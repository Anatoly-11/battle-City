#include "AnimatedSprite.h"
#include <iostream>
#include "Texture2D.h"

namespace Renderer {
  AnimatedSprite::AnimatedSprite(const std::shared_ptr<Texture2D> &pTexture,
    const std::string &initialSubTexture,
    const std::shared_ptr<ShaderProgram> &pShaderProgram,
    const glm::vec2 &position, 
    const glm::vec2 &size, 
    const float rotation) noexcept : Sprite(pTexture, initialSubTexture,
      pShaderProgram, position, size, rotation), m_currentFrame(0), m_currentAnimationTime(0),
    m_dirty(false)/*, m_currentStateName("")*/ {
    m_pCurrentAnimationDurations = m_statesMap.end();
  }

  void AnimatedSprite::setState(const std::string &newState) noexcept {
    auto it = m_statesMap.find(newState);
    if(it == m_statesMap.end()) {
      std::cerr << "Can't find animation state: " << newState << std::endl;
      return;
    }
    //m_currentStateName = newState;
    if(it != m_pCurrentAnimationDurations) {
      m_currentFrame = 0;
      m_currentAnimationTime = 0;
      m_pCurrentAnimationDurations = it;
      m_dirty = true;
    }
  }

  /*const std::string& AnimatedSprite::getState() const noexcept {
    return m_currentStateName;
  }*/

  void AnimatedSprite::insertState(const std::string &state, const std::vector<std::pair<std::string, 
    uint64_t>> &subTextureDuration) noexcept {
    m_statesMap.emplace(state, subTextureDuration);
  }

  void AnimatedSprite::update(const uint64_t delta) noexcept {
    if(m_pCurrentAnimationDurations != m_statesMap.end()) {
      m_currentAnimationTime += delta;
      while(m_currentAnimationTime >= m_pCurrentAnimationDurations->second[m_currentFrame].second) {
        m_currentAnimationTime -= m_pCurrentAnimationDurations->second[m_currentFrame].second;
        ++m_currentFrame;
        m_dirty = true;
        if(m_currentFrame == m_pCurrentAnimationDurations->second.size()) {
          m_currentFrame = 0;
        }
      }
    }
  }

  void AnimatedSprite::render() const noexcept{
    if(m_dirty) {
      auto subTexture = m_pTexture->getSubTexture(m_pCurrentAnimationDurations->second[m_currentFrame].first);
      const GLfloat textureCoords[]{
        // U  V
        subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
        subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
        subTexture.rightTopUV.x, subTexture.rightTopUV.y,
        subTexture.rightTopUV.x, subTexture.rightTopUV.y,
        subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
        subTexture.leftBottomUV.x, subTexture.leftBottomUV.y
      };
      glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureCoords), textureCoords);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      m_dirty = false;
    }
    Sprite::render();
  }
}
