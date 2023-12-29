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
  auto pDefaultShaderProgram = ResourceManager::loadShader("DefaultShader", "res/shaders/vertex.glsl",
    "res/shaders/fragment.glsl");
  if(!pDefaultShaderProgram) {
    std::cerr << "Can't create the default shader program: " << "DefaultShader" << std::endl;
    return false;
  }
  auto pSpriteShaderProgram = ResourceManager::loadShader("SpriteShader", "res/shaders/vSprite.glsl",
    "res/shaders/fSprite.glsl");
  if(!pSpriteShaderProgram) {
    std::cerr << "Can't create the sprite shader program: " << "SpriteShader" << std::endl;
    return false;
  }

  auto tex = ResourceManager::loadTexture("DefaultTexture", "res/textures/map_16x16.png");

  std::vector<std::string> subTextureNames{"block", "topBlock", "bottomBlock", "leftBlock", "rightBlock", "topLeftBlock",
    "bottomLeftBlock", "topRightBlock", "bottomRightBlock", "concrete", "topConcrete", "bottomConcrete",
    "leftConcrete", "rightConcrete", "leftTotConcrete", "rightTopConcrete", "bottomLeftConcrete",
    "bottomRightConcrete", "water1", "water2", "water3", "trees", "ice", "wall", "eagle", "deadEagle",
    "nothing", "respawn1", "respawn2", "respawn3", "respawn4" };

  auto pTextureAtlas = ResourceManager::loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_16x16.png",
    subTextureNames, 16, 16);

  auto pSprite = ResourceManager::loadSprite("NewSprite", "DefaultTextureAtlas", "SpriteShader",
    100, 100, "concrete");
  pSprite->setPosition(glm::vec2(120, 250));

  auto pAnimatedSprite = ResourceManager::loadAnimatedSprite("newAnimetedSprite", "DefaultTextureAtlas", 
    "SpriteShader", 100, 100, "concrete");
  pAnimatedSprite->setPosition(glm::vec2(300, 300));

  pDefaultShaderProgram->use();
  pDefaultShaderProgram->setInt("tex", 0);

  std::vector<std::pair<std::string, uint64_t>> waterState{{"water1", 1000000000}, {"water2", 1000000000},
    {"water3", 1000000000}};

  /*std::vector<std::pair<std::string, uint64_t>> eagleState;
  eagleState.emplace_back(std::make_pair("eagle", 1000000000));
  eagleState.emplace_back(std::make_pair("deadEagle", 1000000000));
  */

  pAnimatedSprite->insertState("waterState", waterState);
  //pAnimatedSprite->insertState("eaglState", eagleState);

  pAnimatedSprite->setState("waterState");

  pDefaultShaderProgram->use();
  pDefaultShaderProgram->setInt("tex", 0);

  glm::mat4 modelMatrix_1(1.f);
  modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 51.f, 0.f));

  glm::mat4 modelMatrix_2(1.f);
  modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(589.f, 51.f, 0.f));

  glm::mat4 projectMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f,
    static_cast<float>(m_windowSize.y), -100.0f, 100.0f);

  pDefaultShaderProgram->setMatrix4("projectionMat", projectMatrix);

  pSpriteShaderProgram->use();
  pSpriteShaderProgram->setInt("tex", 0);
  pSpriteShaderProgram->setMatrix4("projectionMat", projectMatrix);

  std::vector<std::string> TanksSubTextureNames{
    "tankTop1",
    "tankTop2",
    "tankLeft1",
    "tankLeft2",
    "tankBottom1",
    "tankBottom2",
    "tankRight1",
    "tankRight2",
  };
  auto pTankTextureAtlas = ResourceManager::loadTextureAtlas("TanksTextureAtlas", "res/textures/tanks.png",
    TanksSubTextureNames, 16, 16);
  if(!pTankTextureAtlas)
    return false;
  auto pTankAnimatedSprite = ResourceManager::loadAnimatedSprite("TanksAnimetedSprite", "TanksTextureAtlas", 
    "SpriteShader", 100, 100, "tankTop1");
  
  pTankAnimatedSprite->insertState("tankTopState", {{"tankTop1", 500000000}, {"tankTop2", 500000000}});
  pTankAnimatedSprite->insertState("tankLeftState", {{"tankLeft1", 500000000}, {"tankLeft2", 500000000}});
  pTankAnimatedSprite->insertState("tankBottomState", {{"tankBottom1", 500000000}, {"tankBottom2", 500000000}});
  pTankAnimatedSprite->insertState("tankRightState", {{"tankRight1", 500000000}, {"tankRight2", 500000000}});

  pTankAnimatedSprite->setState("tankTopState");
  //pTankAnimatedSprite->setPosition(glm::vec2(100.f, 200.f));

  m_pTank = make_unique<Tank>(pTankAnimatedSprite, 0.0000001f, glm::vec2(100.f, 100.f));

  return true;
}