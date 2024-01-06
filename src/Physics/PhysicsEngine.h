#ifndef _PHYSICSENGINE_H
#define _PHYSICSENGINE_H 1.0

#include <memory>
#include <vector>
#include <unordered_set>
#include <glm/vec2.hpp>

class IGameObject;
class Level;
namespace Physics {

  struct AABB {
    glm::vec2 bottomLeft;
    glm::vec2 topRight;
    AABB(const glm::vec2 &v1, const glm::vec2 &v2) noexcept;
  };

  class PhysicsEngine {
    PhysicsEngine(const PhysicsEngine &) = delete;
    PhysicsEngine &operator=(const PhysicsEngine &) = delete;
    PhysicsEngine(PhysicsEngine &&) = delete;
    PhysicsEngine &operator=(PhysicsEngine &&) = delete;
    ~PhysicsEngine() = delete;
    PhysicsEngine() = delete;
  public:
    static void init() noexcept;
    static void terminate() noexcept;
    static void update(const double delta) noexcept;
    static void addDynamicGameObject(std::shared_ptr<IGameObject> pGameObjects) noexcept;
    static void setCurrentLevel(std::shared_ptr<Level> pLevel) noexcept;
  private:
    static std::unordered_set<std::shared_ptr<IGameObject>> m_dynamicObjects;
    static std::shared_ptr<Level> m_pCurrentLevel;
    static bool hasIntersection(const std::vector<AABB> &colliders1, const glm::vec2 &position1,
      const std::vector<AABB> &colliders2, const glm::vec2 &position2)  noexcept;
  };
}
#endif // _PHYSICSENGINE_H
