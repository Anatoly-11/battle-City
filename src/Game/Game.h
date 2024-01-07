#ifndef _GAME_H
#define _GAME_H 1.0

#include <array>
#include <vector>
#include <glm/vec2.hpp>
#include <memory>

class Tank;
class Level;
class StartScreen;

class Game {
public:
  Game(const glm::ivec2 &_windowSize) noexcept;

  ~Game() noexcept;

  void render() noexcept;

  void update(const double delta) noexcept;

  void setKey(const int key, const int action) noexcept;

  bool init() noexcept;

  unsigned int getCurrentWidth() const noexcept;

  unsigned int  getCurrentHeight() const noexcept;

private:
  enum class EGameState : uint8_t {
    StartScreen,
    LevelStart,
    Level,
    Pause,
    Scores,
    GameOver
  };

  std::array<bool, 349> m_keys;

  glm::ivec2 m_windowSize;

  EGameState m_eCurrentGameState;

  std::shared_ptr<Tank> m_pTank;

  std::shared_ptr<Level> m_pLevel;

  std::shared_ptr<StartScreen> m_pStartScreen;
};
#endif // !_GAME_H