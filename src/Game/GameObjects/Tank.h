#pragma once

#include <memory>
#include <string>
#include <glm/vec2.hpp>
#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"
#include "../../System/Timer.h"

namespace RenderEngine{
  class Sprite;
}

class Bullet;
class AIComponent;

class Tank : public IGameObject {
public:
  enum class ETankType : unsigned int {
    Player1Yellow_type1,
    Player1Yellow_type2,
    Player1Yellow_type3,
    Player1Yellow_type4,

    Player2Green_type1,
    Player2Green_type2,
    Player2Green_type3,
    Player2Green_type4,

    EnemyWhite_type1,
    EnemyWhite_type2,
    EnemyWhite_type3,
    EnemyWhite_type4,

    EnemyGreen_type1,
    EnemyGreen_type2,
    EnemyGreen_type3,
    EnemyGreen_type4,

    EnemyRed_type1,
    EnemyRed_type2,
    EnemyRed_type3,
    EnemyRed_type4
  };

  inline static const std::string TankTypeToSpriteString[] = {
    "player1_yellow_tank_type1_sprite",
    "player1_yellow_tank_type2_sprite",
    "player1_yellow_tank_type3_sprite",
    "player1_yellow_tank_type4_sprite",

    "player2_green_tank_type1_sprite",
    "player2_green_tank_type2_sprite",
    "player2_green_tank_type3_sprite",
    "player2_green_tank_type4_sprite",

    "enemy_white_tank_type1_sprite",
    "enemy_white_tank_type2_sprite",
    "enemy_white_tank_type3_sprite",
    "enemy_white_tank_type4_sprite",

    "enemy_green_tank_type1_sprite",
    "enemy_green_tank_type2_sprite",
    "enemy_green_tank_type3_sprite",
    "enemy_green_tank_type4_sprite",

    "enemy_red_tank_type1_sprite",
    "enemy_red_tank_type2_sprite",
    "enemy_red_tank_type3_sprite",
    "enemy_red_tank_type4_sprite"
  };

  enum class EOrientation : uint8_t {
    Top, Bottom,  Left, Right
  };

  Tank(const Tank::ETankType eType, const bool bHasAI,const bool bShieldOnSpawn, const EOrientation eOrientation,
    const double maxVelocity, const glm::vec2 &position, const glm::vec2 &size, const float layer) noexcept;
  ~Tank() noexcept;
  virtual void render() const noexcept override;

  void setOrientation(const EOrientation eOrientation) noexcept;

  virtual void update(const double delta) noexcept override;

  double getMaxVelocity() const noexcept;

  virtual void setVelocity(const double velocity) noexcept override;

  void fire() const noexcept;


private:
  EOrientation m_eOrientation;
  std::shared_ptr<Bullet> m_pCurrentBullet;
  std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
  std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
  std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
  std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;
  std::shared_ptr<RenderEngine::Sprite> m_pSprite_respawn;
  std::shared_ptr<RenderEngine::Sprite> m_pSprite_shield;

  RenderEngine::SpriteAnimator m_spriteAnimator_top;
  RenderEngine::SpriteAnimator m_spriteAnimator_bottom;
  RenderEngine::SpriteAnimator m_spriteAnimator_left;
  RenderEngine::SpriteAnimator m_spriteAnimator_right;
  RenderEngine::SpriteAnimator m_spriteAnimator_respawn;
  RenderEngine::SpriteAnimator m_spriteAnimator_shield;
  
  Timer m_respawnTimer;
  Timer m_shieldTimer;

  double m_maxVelocity;
  bool m_isSpawning;
  bool m_hasShield;
  bool m_bShieldOnSpawn;

  std::unique_ptr<AIComponent> m_pAIComponent;

  static const std::string &getTankSpriteFromType(const Tank::ETankType eType) noexcept;
 };