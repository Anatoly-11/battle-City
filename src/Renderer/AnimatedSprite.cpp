#include "AnimatedSprite.h"
#include <iostream>
#include "Texture2D.h"

using namespace std;
using namespace glm;

namespace Renderer {
  AnimatedSprite::AnimatedSprite(const shared_ptr<Texture2D> &pTexture,
    const string &initialSubTexture, const shared_ptr<ShaderProgram> &pShaderProgram,
    const vec2 &position, const vec2 &size, const float rotation) noexcept : Sprite(pTexture, initialSubTexture,
      pShaderProgram, position, size, rotation), m_currentFrame(0), m_currentAnimationTime(0),
    m_dirty(false) {
    m_pCurrentAnimationDurations = m_statesMap.end();
  }

  void AnimatedSprite::setState(const std::string &newState) noexcept {
    auto it = m_statesMap.find(newState);
    if(it == m_statesMap.end()) {
      std::cerr << "Can't find animation state: " << newState << std::endl;
      return;
    }
    if(it != m_pCurrentAnimationDurations) {
      m_currentFrame = 0;
      m_currentAnimationTime = 0;
      m_pCurrentAnimationDurations = it;
      m_dirty = true;
    }
  }

  void AnimatedSprite::insertState(const string &state, const vector<pair<string, 
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
