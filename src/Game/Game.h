#pragma once
#ifndef _GAME_H
#define _GAME_H 1.0

#include <array>
#include <glm/vec2.hpp>


class Game {
public:
  Game(const glm::ivec2 &_windowSize) noexcept;
  ~Game() noexcept;
  void render() noexcept;
  void update(const uint64_t delta) noexcept;
  void setKey(const int key, const int action) noexcept;
  bool init() noexcept;
private:
  std::array<bool, 349> m_keys;

  enum class EGameState {
    Active,
    Paused
  };

  EGameState m_eCurrentGameState;

  glm::ivec2 m_windowSize;
};
#endif // !_GAME_H