#include "Game.h"

#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include <iostream>
#include <fstream>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Level.h"
#include "GameObjects/Tank.h"

Game::Game(const glm::ivec2 &_windowSize) noexcept : m_eCurrentGameState(EGameState::Active),
  m_windowSize(_windowSize) {
  m_keys.fill(false);
}

Game::~Game() noexcept {
}

void Game::render() noexcept {
  if(m_pTank != nullptr) {
    m_pTank->render();
  }

  if(m_pLevel) {
    m_pLevel->render();;
  }
}


void Game::update(const uint64_t delta) noexcept {
  if(m_pLevel) {
    m_pLevel->update(delta);
  }
  if(m_pTank != nullptr) {
    if(m_keys[GLFW_KEY_W] || m_keys[GLFW_KEY_UP]) {
      m_pTank->setOrientation(Tank::EOrientation::Top);
      m_pTank->move(true);
    } else if(m_keys[GLFW_KEY_A] || m_keys[GLFW_KEY_LEFT]) {
      m_pTank->setOrientation(Tank::EOrientation::Left);
      m_pTank->move(true);
    } else if(m_keys[GLFW_KEY_D] || m_keys[GLFW_KEY_RIGHT]) {
      m_pTank->setOrientation(Tank::EOrientation::Right);
      m_pTank->move(true);
    } else if(m_keys[GLFW_KEY_S] || m_keys[GLFW_KEY_DOWN]) {
      m_pTank->setOrientation(Tank::EOrientation::Bottom);
      m_pTank->move(true);
    } else if(m_keys[GLFW_KEY_P]) {
      m_pTank->move(false);
    } else if(m_keys[GLFW_KEY_G]) {
      m_pTank->move(true);
    }
  } 
  m_pTank->update(delta);
}

void Game::setKey(const int key, const int action) noexcept {
  m_keys[key] = action;
}

bool Game::init() noexcept {

  ResourceManager::loadJSONResources("res/resources.json");

  auto pSpriteShaderProgram = ResourceManager::getShaderProgram("spriteShader");
  if(!pSpriteShaderProgram) {
    std::cerr << "Can't find shader prordam: spriteShader..." << std::endl;
    return false;
  }

  auto pTextureAtlas = ResourceManager::getTexture("mapTextureAtlas");
  if(!pTextureAtlas) {
    std::cerr << "Can't find texture atlas: mapTextureAtlas..." << std::endl;
    return false;
  }

  auto pTankTextureAtlas = ResourceManager::getTexture("tanksTextureAtlas");
  if(!pTankTextureAtlas) {
    std::cerr << "Can't find texture atlas: pTankTextureAtlas..." << std::endl;
    return false;
  }
   
  glm::mat4 projectMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f,
    static_cast<float>(m_windowSize.y), -100.0f, 100.0f);

  pSpriteShaderProgram->use();
  pSpriteShaderProgram->setInt("tex", 0);
  pSpriteShaderProgram->setMatrix4("projectionMat", projectMatrix);

  auto pTankAnimatedSprite = ResourceManager::getAnimatedSprite("tankAnimatedSprite");
  if(!pTankAnimatedSprite) {
    std::cerr << "Can't find animated sprite: tankAnimatedSprite..." << std::endl;
    return false;
  }

  m_pTank = make_unique<Tank>(pTankAnimatedSprite, 5.e-8f, glm::vec2(0.f, 0.f), glm::vec2(16.f, 16.f));

  m_pLevel = make_unique<Level>(ResourceManager::getLevels()[0]);

  return true;
}