#pragma once

#include <memory>
#include <vector>
#include <string>
#include <glm/vec2.hpp>

#include "IGameState.h"
#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine {
  class Sprite;
}

class Game;

class StartScreen : public IGameState {
public:
  static constexpr unsigned int BLOCK_SIZE = 8;
  static constexpr unsigned int STARTSCREEN_WIDTH = 15 * BLOCK_SIZE * 2;
  static constexpr unsigned int STARTSCREEN_HEIGHT = 14 * BLOCK_SIZE * 2;
  static constexpr unsigned int MENU_WIDTH = 128;
  static constexpr unsigned int MENU_HEIGHT = 64;
  static constexpr unsigned int TANK_SIZE = BLOCK_SIZE * 2;


  StartScreen(const std::vector<std::string> &startScreenDescription, Game *pGame) noexcept;

  virtual void render() const noexcept override;
  virtual void update(const double delta) noexcept override;
  virtual void processInput(int &key, int &mode) noexcept override;

  virtual unsigned int getStateWidth() const  noexcept override;
  virtual unsigned int getStateHeight() const  noexcept override;

private:
  static constexpr int MAX_MENU_INDEX = 2;
  Game *m_pGame;
  //bool m_keyReleased;
  int m_currentMenuIndex;
  std::vector<std::pair<std::shared_ptr<RenderEngine::Sprite>, glm::vec2>> m_sprites;
  std::pair<std::shared_ptr<RenderEngine::Sprite>, glm::vec2> m_menuSprite;
  std::pair<std::shared_ptr<RenderEngine::Sprite>, glm::vec2> m_tankSprite;
  RenderEngine::SpriteAnimator m_tankSpriteAnimator;
};