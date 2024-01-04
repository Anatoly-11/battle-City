#ifndef _GAME_H
#define _GAME_H 1.0

#include <array>
#include <vector>
#include <glm/vec2.hpp>
#include <memory>

class Tank;
class Level;

class Game {
public:
  Game(const glm::ivec2 &_windowSize) noexcept;
  ~Game() noexcept;

  void render() noexcept;

  void update(const uint64_t delta) noexcept;

  void setKey(const int key, const int action) noexcept;

  bool init() noexcept;

  size_t getCurrentLevelWidth() const noexcept;

  size_t getCurrentLevelHeight() const noexcept;

private:
  std::array<bool, 349> m_keys;

  enum class EGameState {
    Active,
    Paused
  };

  EGameState m_eCurrentGameState;

  glm::ivec2 m_windowSize;

  std::unique_ptr<Tank> m_pTank;

  std::unique_ptr<Level> m_pLevel;
};
#endif // !_GAME_H