#include "PhysicsEngine.h"
#include "../Game/GameObjects/IGameObject.h"

std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::m_dymamicObjects;

void PhysicsEngine::init() noexcept {

}

void PhysicsEngine::trminate() noexcept {
  m_dymamicObjects.clear();
}

void PhysicsEngine::update(const double delta) noexcept {
  for(auto &currentObject : m_dymamicObjects) {
    if(currentObject->getCurrentVelocity() > 0) {
      currentObject->getCurrentPosition() += currentObject->getCurrentDirection()
        * static_cast<float>(currentObject->getCurrentVelocity() * delta);
    }
  }
}

void PhysicsEngine::addDymamycObject(std::shared_ptr<IGameObject> pGameObjects) noexcept {
  m_dymamicObjects.insert(std::move(pGameObjects));
}
