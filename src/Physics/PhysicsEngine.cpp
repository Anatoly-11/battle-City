#include "PhysicsEngine.h"
#include "../Game/GameObjects/IGameObject.h"
#include "../Game/Level.h"

namespace Physics {

  std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::m_dymamicObjects;
  std::shared_ptr<Level> PhysicsEngine::m_pCurrentLevel;

  AABB::AABB(const glm::vec2 &v1, const glm::vec2 &v2) noexcept : bottomLeft(v1), topRight(v2) {
  }

  void PhysicsEngine::init() noexcept {

  }

  void PhysicsEngine::terminate() noexcept {
    m_dymamicObjects.clear();
    m_pCurrentLevel.reset();
  }

  void PhysicsEngine::update(const double delta) noexcept {
    for(auto &currentObject : m_dymamicObjects) {
      float velocity = currentObject->getCurrentVelocity();
      if(velocity > 0) {
        const auto currentPosition = currentObject->getCurrentPosition();
        const auto newPosition = currentPosition  + currentObject->getCurrentDirection() * static_cast<float>(velocity * delta);
        const auto &colliders = currentObject->getCollisers();
        std::vector<std::shared_ptr<IGameObject>> objectsToCheck = m_pCurrentLevel->getObjectsInArea(newPosition,
          newPosition + currentObject->getSize());

        bool hasCollision = false;

        for(const auto &currentObjectToCheck : objectsToCheck) {
          const auto &collidersToCheck = currentObjectToCheck->getCollisers();
          if(!collidersToCheck.empty()) {
            if(hasIntersection(colliders, newPosition, collidersToCheck, currentPosition)) {
              hasCollision = true;
              break;
            }
          }
        }
        if(!hasCollision) {
          currentObject->getCurrentPosition() = newPosition;
        }
      }
    }
  }

  void PhysicsEngine::addDymamycObject(std::shared_ptr<IGameObject> pGameObjects) noexcept {
    m_dymamicObjects.insert(std::move(pGameObjects));
  }

  void PhysicsEngine::setCurrentLevel(std::shared_ptr<Level> pLevel) noexcept {
    m_pCurrentLevel.swap(pLevel);
  }

  bool PhysicsEngine::hasIntersection(const std::vector<AABB> &colliders1, const glm::vec2 &position1,
    const std::vector<AABB> &colliders2, const glm::vec2 &position2)  noexcept {
    for(const auto &currentCollider1 : colliders1) {
      const glm::vec2 currentCollider1_bottomLeft_world = currentCollider1.bottomLeft + position1;
      const glm::vec2 currentCollider1_topRight_world   = currentCollider1.topRight   + position1;
      for(const auto &currentCollider2 : colliders2) {
        const glm::vec2 currentCollider2_bottomLeft_world = currentCollider2.bottomLeft + position2;
        const glm::vec2 currentCollider2_topRight_world   = currentCollider2.topRight   + position2;
        if(currentCollider1_bottomLeft_world.x >= currentCollider2_topRight_world.x) { // первый объект целиком справа по x
          return false;
        }
        if(currentCollider1_topRight_world.x <= currentCollider2_bottomLeft_world.x) { // первый объект целиком справа по x
          return false;
        }
        if(currentCollider1_bottomLeft_world.y >= currentCollider2_topRight_world.y) { // первый объект целиком сверху по y
          return false;
        }
        if(currentCollider1_topRight_world.y <= currentCollider2_bottomLeft_world.y) { // первый объект целиком снизу по y
          return false;
        }
      }
    }
    return true;
  }
}