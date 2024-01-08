#include "Level.h"

#include "../GameObjects/BrickWall.h"
#include "../GameObjects/BetonWall.h"
#include "../GameObjects/Trees.h"
#include "../GameObjects/Ice.h"
#include "../GameObjects/Water.h"
#include "../GameObjects/Eagle.h"
#include "../GameObjects/Border.h"
#include "../GameObjects/Tank.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <algorithm>
#include <cmath>


std::shared_ptr<IGameObject> createGameObjectFromDescription(const char description, const glm::vec2 &position,
  const glm::vec2 &size, const float rotation) noexcept {
  switch(description)
  {
  case '0':
    return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Right, position, size, rotation, 0.f);
  case '1':
    return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Bottom, position, size, rotation, 0.f);
  case '2':
    return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Left, position, size, rotation, 0.f);
  case '3':
    return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Top, position, size, rotation, 0.f);
  case '4':
    return std::make_shared<BrickWall>(BrickWall::EBrickWallType::All, position, size, rotation, 0.f);
  case 'G':
    return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomLeft, position, size, rotation, 0.f);
  case 'H':
    return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomRight, position, size, rotation, 0.f);
  case 'I':
    return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopLeft, position, size, rotation, 0.f);
  case 'J':
    return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopRight, position, size, rotation, 0.f);
  case '5':
    return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Right, position, size, rotation, 0.f);
  case '6':
    return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Bottom, position, size, rotation, 0.f);
  case '7':
    return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Left, position, size, rotation, 0.f);
  case '8':
    return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Top, position, size, rotation, 0.f);
  case '9':
    return std::make_shared<BetonWall>(BetonWall::EBetonWallType::All, position, size, rotation, 0.f);
  case 'A':
    return std::make_shared<Water>(position, size, rotation, 0.f);
  case 'B':
    return std::make_shared<Trees>(position, size, rotation, 1.f);
  case 'C':
    return std::make_shared<Ice>(position, size, rotation, -1.f);
  case 'E':
    return std::make_shared<Eagle>(position, size, rotation, 0.f);
  case 'D':
    return nullptr;
  default:
    std::cerr << "Unknown GameObject description: '" << description << '\'' << std::endl;
    break;
  }
  return nullptr;
}

Level::Level(const std::vector<std::string> &levelDescription) noexcept {
  if(levelDescription.empty()) {
    std::cerr << "Empty level description..." << std::endl;
    return;
  }
  m_widthBlocks = levelDescription[0].length();
  m_heightBlocks = levelDescription.size();
  m_widthPixels = m_widthBlocks * BLOCK_SIZE;
  m_heightPixels = m_heightBlocks * BLOCK_SIZE;

  m_playerRespawn_1 = {BLOCK_SIZE * ((m_widthBlocks >> 1) - 1), BLOCK_SIZE >> 1};
  m_playerRespawn_2 = {BLOCK_SIZE * ((m_widthBlocks >> 1) + 3), BLOCK_SIZE >> 1};
  m_enemyRespawn_1  = {BLOCK_SIZE,                        BLOCK_SIZE * (m_heightBlocks - 0.5f)};
  m_enemyRespawn_2  = {BLOCK_SIZE * ((m_widthBlocks >> 1) + 1), BLOCK_SIZE * (m_heightBlocks - 0.5f)};
  m_enemyRespawn_3  = {BLOCK_SIZE * m_widthBlocks,              BLOCK_SIZE * (m_heightBlocks - 0.5f)};
  
  m_levelObjects.reserve(m_widthBlocks * m_heightBlocks + 4);
    unsigned int currentBottonOffset = BLOCK_SIZE * (m_heightBlocks - 0.5f);
  for(const std::string &currentRow : levelDescription) {
    unsigned int currentLeftOffset = BLOCK_SIZE;
    for(const char currentElement : currentRow) {
      switch(currentElement) {
      case 'K':
        m_playerRespawn_1 = {currentLeftOffset, currentBottonOffset};
        m_levelObjects.emplace_back(nullptr);
        break;
      case 'L':
        m_playerRespawn_2 = {currentLeftOffset, currentBottonOffset};
        m_levelObjects.emplace_back(nullptr);
        break;
      case 'M':
        m_enemyRespawn_1 = {currentLeftOffset, currentBottonOffset};
        m_levelObjects.emplace_back(nullptr);
        break;
      case 'N':
        m_enemyRespawn_2 = {currentLeftOffset, currentBottonOffset};
        m_levelObjects.emplace_back(nullptr);
        break;
      case 'O':
        m_enemyRespawn_3 = {currentLeftOffset, currentBottonOffset};
        m_levelObjects.emplace_back(nullptr);
        break;
      default:
        m_levelObjects.emplace_back(createGameObjectFromDescription(currentElement, glm::vec2(currentLeftOffset,
          currentBottonOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
        break;
      }
      currentLeftOffset += BLOCK_SIZE;
    }
    currentBottonOffset -= BLOCK_SIZE;
  }

  // bottom border
  m_levelObjects.emplace_back(std::make_shared<Border>(glm::vec2((float)BLOCK_SIZE, 0.f),
    glm::vec2(m_widthBlocks * BLOCK_SIZE, BLOCK_SIZE >> 1), 0.f, 0.f));
  // top border
  m_levelObjects.emplace_back(std::make_shared<Border>(glm::vec2((float)BLOCK_SIZE, (m_heightBlocks + 0.5f) * BLOCK_SIZE),
    glm::vec2(m_widthBlocks * BLOCK_SIZE, BLOCK_SIZE >> 1), 0.f, 0.f));
  // left border
  m_levelObjects.emplace_back(std::make_shared<Border>(glm::vec2(0.f),
    glm::vec2(BLOCK_SIZE, (m_heightBlocks + 1.f) * BLOCK_SIZE), 0.f, 0.f));
  // right border
  m_levelObjects.emplace_back(std::make_shared<Border>(glm::vec2((m_widthBlocks + 1) * BLOCK_SIZE, 0.f),
    glm::vec2(BLOCK_SIZE << 1, (m_heightBlocks + 1.f) * BLOCK_SIZE), 0.f, 0.f));
 
}


unsigned int Level::getStateWidth() const noexcept {
  return (m_widthBlocks + 3) * BLOCK_SIZE;
}

unsigned int Level::getStateHeight() const noexcept {
  return (m_heightBlocks + 1) * BLOCK_SIZE;
}

void Level::processInput(const std::array<bool, 349> &aKeys) noexcept {
  if(m_pTank) {
    if(aKeys[GLFW_KEY_W] || aKeys[GLFW_KEY_UP]) {
      m_pTank->setOrientation(Tank::EOrientation::Top);
      m_pTank->setVelocity(m_pTank->getMaxVelocity());
    } else if(aKeys[GLFW_KEY_A] || aKeys[GLFW_KEY_LEFT]) {
      m_pTank->setOrientation(Tank::EOrientation::Left);
      m_pTank->setVelocity(m_pTank->getMaxVelocity());
    } else if(aKeys[GLFW_KEY_D] || aKeys[GLFW_KEY_RIGHT]) {
      m_pTank->setOrientation(Tank::EOrientation::Right);
      m_pTank->setVelocity(m_pTank->getMaxVelocity());
    } else if(aKeys[GLFW_KEY_S] || aKeys[GLFW_KEY_DOWN]) {
      m_pTank->setOrientation(Tank::EOrientation::Bottom);
      m_pTank->setVelocity(m_pTank->getMaxVelocity());
    } else {
      m_pTank->setVelocity(0);
    }

    if(m_pTank && aKeys[GLFW_KEY_SPACE]) {
      m_pTank->fire();
    }
  }
}

void Level::initPhysics() noexcept {
  m_pTank = std::make_shared<Tank>(0.05, getPlayerRespawn_1(), 
   glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE), 0.f);
  Physics::PhysicsEngine::addDynamicGameObject(m_pTank);
}

void Level::render() const noexcept {
  for(const auto &currentMapObject : m_levelObjects) {
    if(currentMapObject) {
      currentMapObject->render();
    }
  }
  m_pTank->render();
}

void Level::update(const double delta) noexcept {
  for(const auto &currentMapObject : m_levelObjects) {
    if(currentMapObject) {
      currentMapObject->update(delta);
    }
  }
  m_pTank->update(delta);
}

const glm::ivec2 &Level::getPlayerRespawn_1() const noexcept {
  return m_playerRespawn_1;
}

const glm::ivec2 &Level::getPlayerRespawn_2() const noexcept {
  return m_playerRespawn_2;
}

const glm::ivec2 &Level::getEnemyRespawn_1() const noexcept {
  return m_enemyRespawn_1;
}

const glm::ivec2 &Level::getEnemyRespawn_2() const noexcept {
  return m_enemyRespawn_2;
}

const glm::ivec2 &Level::getEnemyRespawn_3() const noexcept {
  return m_enemyRespawn_3;
}

std::vector<std::shared_ptr<IGameObject>> Level::getObjectsInArea(const glm::vec2 &bottomLeft,
  const glm::vec2 &topRight) const noexcept {
  std::vector<std::shared_ptr<IGameObject>> output;
  output.reserve(9);

  glm::vec2 bottomLeft_converted(std::clamp(bottomLeft.x - BLOCK_SIZE, 0.f, static_cast<float>(m_widthPixels)),
    std::clamp(m_heightPixels - bottomLeft.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_heightPixels)));
  glm::vec2 topRight_converted(std::clamp(topRight.x - BLOCK_SIZE, 0.f, static_cast<float>(m_widthPixels)),
    std::clamp(m_heightPixels - topRight.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_heightPixels)));

  unsigned int startX = static_cast<unsigned int>(floor(bottomLeft_converted.x / BLOCK_SIZE));
  unsigned int endX = static_cast<unsigned int>(ceil(topRight_converted.x / BLOCK_SIZE));

  unsigned int startY = static_cast<unsigned int>(floor(topRight_converted.y / BLOCK_SIZE));
  unsigned int endY = static_cast<unsigned int>(ceil(bottomLeft_converted.y / BLOCK_SIZE));

  for(unsigned int currentColumn = startX; currentColumn < endX; ++currentColumn) {
    for(unsigned int currentRow = startY; currentRow < endY; ++currentRow) {

      if(auto &currentObject = m_levelObjects[currentColumn + currentRow * m_widthBlocks]; currentObject != nullptr) {
        output.push_back(currentObject);
      }
    }
  }

  if(endX >= m_widthBlocks) {
    output.push_back(m_levelObjects[m_levelObjects.size() - 1]);
  }
  if(startX <= 1) {
    output.push_back(m_levelObjects[m_levelObjects.size() - 2]);
  }
  if(startY <= 1) {
    output.push_back(m_levelObjects[m_levelObjects.size() - 3]);
  }
  if(endY >= m_heightBlocks) {
    output.push_back(m_levelObjects[m_levelObjects.size() - 4]);
  }
  return output;
}