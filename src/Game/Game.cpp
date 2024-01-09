#include "Game.h"

#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include "GameObjects/Tank.h"
#include "GameObjects/Bullet.h"

#include "GameStates/Level.h"
#include "GameStates/StartScreen.h"
#include "../Physics/PhysicsEngine.h"
#include "../Renderer/Renderer.h"

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


Game::Game(const glm::ivec2 &_windowSize) noexcept : m_key(-1), m_mode(-1), m_act(-1),
  m_windowSize(_windowSize), 
  m_eCurrentGameState(EGameState::StartScreen) {
}

Game::~Game() noexcept {
}


void Game::render() noexcept {
  m_pCurrentGameState->render();
}

void Game::update(const double delta) noexcept {
  m_pCurrentGameState->processInput(m_key, m_act, m_mode);
  m_pCurrentGameState->update(delta);
}

void Game::setKey(const int key, const int act, const int mode) noexcept {
  m_key = key;
  m_act = act;
  m_mode = mode;
}

bool Game::init() noexcept {

  ResourceManager::loadJSONResources("res/resources.json");

  m_pSpriteShaderProgram = ResourceManager::getShaderProgram("spriteShader");
  if(!m_pSpriteShaderProgram) {
    std::cerr << "Can't find shader prordam: spriteShader..." << std::endl;
    return false;
  }
  m_pSpriteShaderProgram->use();
  m_pSpriteShaderProgram->setInt("tex", 0);

  m_pCurrentGameState = std::make_shared<StartScreen>(ResourceManager::getStartScreen(), this);
  setWindowSize(m_windowSize);
  return true;
}

void Game::setWindowSize(const glm::uvec2 &windowSize) noexcept {
  m_windowSize = windowSize;
  updateViewport();
}
void Game::updateViewport() noexcept {
  const float level_aspect_ratio = static_cast<float>(getCurrentWidth()) / getCurrentHeight();
  unsigned int viewPortWidth = m_windowSize.x;
  unsigned int viewPortHeight = m_windowSize.y;
  unsigned int viewPortLeftOffset = 0;
  unsigned int viewPortBottomOffset = 0;

  if(static_cast<float>(m_windowSize.x) / m_windowSize.y > level_aspect_ratio) {
    viewPortWidth = static_cast<unsigned int>(m_windowSize.y * level_aspect_ratio);
    viewPortLeftOffset = (m_windowSize.x - viewPortWidth) / 2;
  } else {
    viewPortHeight = static_cast<unsigned int>(m_windowSize.x / level_aspect_ratio);
    viewPortBottomOffset = (m_windowSize.y - viewPortHeight) / 2;
  }

  RenderEngine::Renderer::setViewport(viewPortWidth, viewPortHeight, viewPortLeftOffset, viewPortBottomOffset);

  glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(getCurrentWidth()),
    0.f, static_cast<float>(getCurrentHeight()), -100.f, 100.f);
  m_pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);
}

void Game::startNewLevel(const unsigned int level, const EGameMode eGameMode) noexcept {
  m_currentLevelIndex = level;
  auto pLevel = std::make_shared<Level>(ResourceManager::getLevels()[m_currentLevelIndex], eGameMode);
  m_pCurrentGameState = pLevel;
  Physics::PhysicsEngine::setCurrentLevel(pLevel);
  updateViewport();
  /*if(m_pCurrentGameState != pLevel) {
    if(m_pCurrentGameState)
      m_pCurrentGameState.reset();
    m_pCurrentGameState = pLevel;
    Physics::PhysicsEngine::setCurrentLevel(pLevel);
    updateViewport();
  }*/
}

void Game::nextLevel(const EGameMode eGameMode) noexcept {
  startNewLevel(++m_currentLevelIndex, eGameMode);
}

unsigned int Game::getCurrentWidth() const noexcept {
  return m_pCurrentGameState->getStateWidth();
}

unsigned int Game::getCurrentHeight() const noexcept {
  return m_pCurrentGameState->getStateHeight();
}