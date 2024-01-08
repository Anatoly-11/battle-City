#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <unordered_set>
#include <glm/vec2.hpp>

class IGameObject;
class Level;
namespace Physics {
  enum class ECollisionDirection : uint8_t {
    Top,
    Bottom,
    Left,
    Right
  };

  struct AABB {
    glm::vec2 bottomLeft;
    glm::vec2 topRight;
    AABB(const glm::vec2 &v1, const glm::vec2 &v2) noexcept;
  };

  struct Collider {
    Collider(const glm::vec2 &_bottomLeft, const glm::vec2 _topRight,
      std::function<void(const IGameObject &, const ECollisionDirection)> _onCollisionCallback = {}) noexcept;

    Collider(const AABB &_boundingBox, std::function<void(const IGameObject &, const ECollisionDirection)>
      _onCollisionCallback = {}) noexcept;

    AABB boundingBox;
    bool isActive;
    std::function<void(const IGameObject &, const ECollisionDirection)> onCollisionCallback;
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
    static bool hasIntersection(const Collider& collider1, const glm::vec2& position1, const Collider& collider2,
      const glm::vec2& position2) noexcept;
  };
}