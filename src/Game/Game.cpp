#include "Game.h"

#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include <iostream>
#include <fstream>

#include "Tank.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

//std::ofstream log_f;
//std::streambuf *cerrbuf = std::cerr.rdbuf(); //запомним старый буфер

Game::Game(const glm::ivec2 &_windowSize) noexcept : m_eCurrentGameState(EGameState::Active),
  m_windowSize(_windowSize) {
  m_keys.fill(false);
  //log_f.open("LOG<LG", std::ios_base::ate);
  //std::cerr.set_rdbuf(log_f.rdbuf());
}

Game::~Game() noexcept {
  //delete m_pTank;
  //log_f.close();
  //std::cerr.rdbuf(cerrbuf);
}

void Game::render() noexcept {
  //resourceManager->getSprite("NewSprite")->render();
  ResourceManager::getAnimatedSprite("newAnimetedSprite")->render();
  if(m_pTank != nullptr) {
    m_pTank->render();
  }
}

void Game::update(const uint64_t delta) noexcept {
  ResourceManager::getAnimatedSprite("newAnimetedSprite")->update(delta);
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

  auto pAnimatedSprite = ResourceManager::loadAnimatedSprite("newAnimetedSprite", "mapTextureAtlas", 
    "spriteShader", 100, 100, "concrete");
  pAnimatedSprite->setPosition(glm::vec2(300, 300));

  std::vector<std::pair<std::string, uint64_t>> waterState{{"water1", 1000000000}, {"water2", 1000000000},
    {"water3", 1000000000}};

  pAnimatedSprite->insertState("waterState", waterState);

  pAnimatedSprite->setState("waterState");

  /*glm::mat4 modelMatrix_1(1.f);
  modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 51.f, 0.f));

  glm::mat4 modelMatrix_2(1.f);
  modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(589.f, 51.f, 0.f));*/

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

  m_pTank = make_unique<Tank>(pTankAnimatedSprite, 0.0000001f, glm::vec2(100.f, 100.f));

  return true;
}