#pragma once

#include <array>
#include <glm/vec2.hpp>
#include <memory>
namespace RenderEngine {
  class ShaderProgram;
}

class IGameState;

class Game {
public:
  enum class EGameMode : uint8_t {
    OnePlayer,
    TwoPlayers
  };

  Game(const glm::ivec2 &_windowSize) noexcept;

  ~Game() noexcept;

  void render() noexcept;

  void update(const double delta) noexcept;

  void setKey(const int key, const int action) noexcept;

  bool init() noexcept;

  void startNewLevel(const unsigned int level, const EGameMode eGameMode) noexcept;

  void nextLevel(const EGameMode eGameMode) noexcept;

  unsigned int getCurrentWidth() const noexcept;

  unsigned int  getCurrentHeight() const noexcept;
  
  void updateViewport() noexcept;
  
  void setWindowSize(const glm::uvec2& windowSize) noexcept;
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
  
  std::shared_ptr<IGameState> m_pCurrentGameState;
  std::shared_ptr<RenderEngine::ShaderProgram> m_pSpriteShaderProgram;
  unsigned int m_currentLevelIndex;
};