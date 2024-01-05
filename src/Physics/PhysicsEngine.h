#ifndef _PHYSICSENGINE_H
#define _PHYSICSENGINE_H 1.0

#include <memory>
#include <unordered_set>

class IGameObject;

class PhysicsEngine {
  PhysicsEngine(const PhysicsEngine&) = delete;
  PhysicsEngine &operator=(const PhysicsEngine&) = delete;
  PhysicsEngine(PhysicsEngine&&) = delete;
  PhysicsEngine &operator=(PhysicsEngine&&) = delete;
  ~PhysicsEngine() = delete;
  PhysicsEngine() = delete;
public:
  static void init() noexcept;
  static void trminate() noexcept;
  static void update(const double delta) noexcept;
  static void addDymamycObject(std::shared_ptr<IGameObject> pGameObjects) noexcept;
private:
  static std::unordered_set<std::shared_ptr<IGameObject>> m_dymamicObjects;
};
#endif // _PHYSICSENGINE_H
