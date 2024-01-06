#include "Game.h"

#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Physics/PhysicsEngine.h"
#include <iostream>
#include <fstream>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Level.h"
#include "GameObjects/Tank.h"
#include "GameObjects/Bullet.h"

Game::Game(const glm::ivec2 &_windowSize) noexcept : m_windowSize(_windowSize), m_eCurrentGameState(EGameState::Active) {
  m_keys.fill(false);
}

Game::~Game() noexcept {
}

void Game::render() noexcept {
  if(m_pTank != nullptr) {
    m_pTank->render();
  }

  if(m_pLevel) {
    m_pLevel->render();
  }
}


void Game::update(const double delta) noexcept {
  if(m_pLevel) {
    m_pLevel->update(delta);
  }
  if(m_pTank != nullptr) {
    if(m_keys[GLFW_KEY_W] || m_keys[GLFW_KEY_UP]) {
      m_pTank->setOrientation(Tank::EOrientation::Top);
      m_pTank->setVelocity(m_pTank->getMaxVelocity());
    } else if(m_keys[GLFW_KEY_A] || m_keys[GLFW_KEY_LEFT]) {
      m_pTank->setOrientation(Tank::EOrientation::Left);
      m_pTank->setVelocity(m_pTank->getMaxVelocity());
    } else if(m_keys[GLFW_KEY_D] || m_keys[GLFW_KEY_RIGHT]) {
      m_pTank->setOrientation(Tank::EOrientation::Right);
      m_pTank->setVelocity(m_pTank->getMaxVelocity());
    } else if(m_keys[GLFW_KEY_S] || m_keys[GLFW_KEY_DOWN]) {
      m_pTank->setOrientation(Tank::EOrientation::Bottom);
      m_pTank->setVelocity(m_pTank->getMaxVelocity());
    } else {
      m_pTank->setVelocity(0);
    }
    if(m_keys[GLFW_KEY_SPACE]) {
      m_pTank->fire();
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

  m_pLevel = std::make_shared<Level>(ResourceManager::getLevels()[0]);
  m_windowSize.x = static_cast<int>(m_pLevel->getLevelWidth());
  m_windowSize.y = static_cast<int>(m_pLevel->getLevelHeight());

  Physics::PhysicsEngine::setCurrentLevel(m_pLevel);


  glm::mat4 projectMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.0f, 100.0f);

  pSpriteShaderProgram->use();
  pSpriteShaderProgram->setInt("tex", 0);
  pSpriteShaderProgram->setMatrix4("projectionMat", projectMatrix);
  m_pTank = std::make_shared<Tank>(0.05, m_pLevel->getPlayerRespawn_1(), 
    glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE), 0.f);
  Physics::PhysicsEngine::addDynamicGameObject(m_pTank);
  return true;
}

size_t Game::getCurrentLevelWidth() const noexcept {
  return m_pLevel->getLevelWidth();
}

size_t Game::getCurrentLevelHeight() const noexcept {
  return m_pLevel->getLevelHeight();
}