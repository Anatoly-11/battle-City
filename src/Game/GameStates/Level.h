#pragma once

#include <string>
#include <vector>

#include "IGameState.h"
#include <memory>

#include <glm/vec2.hpp>

class IGameObject;

class Tank;


class Level : public IGameState {
public:
	static constexpr unsigned int BLOCK_SIZE = 16;

	Level(const std::vector<std::string> &levelDescription) noexcept;
	virtual void render() const noexcept override;
	virtual void update(const double delta) noexcept override;

	virtual unsigned int getStateWidth() const noexcept override;
  virtual unsigned int getStateHeight() const noexcept override;
	virtual void processInput(const std::array<bool, 349> &aKeys) noexcept override;

	const glm::ivec2 &getPlayerRespawn_1() const noexcept;
	const glm::ivec2 &getPlayerRespawn_2() const noexcept;
	const glm::ivec2 &getEnemyRespawn_1() const noexcept;
	const glm::ivec2 &getEnemyRespawn_2() const noexcept;
	const glm::ivec2 &getEnemyRespawn_3() const noexcept;

	std::vector<std::shared_ptr<IGameObject>> getObjectsInArea(const glm::vec2 &bottomLeft,
		const glm::vec2 &topRight) const noexcept;
	void initPhysics() noexcept;
private:
	unsigned int m_widthBlocks;
	unsigned int m_heightBlocks;
	unsigned int m_widthPixels;
	unsigned int m_heightPixels;

	glm::ivec2 m_playerRespawn_1;
	glm::ivec2 m_playerRespawn_2;
	glm::ivec2 m_enemyRespawn_1;
	glm::ivec2 m_enemyRespawn_2;
	glm::ivec2 m_enemyRespawn_3;

	std::vector<std::shared_ptr<IGameObject>> m_levelObjects;
	std::shared_ptr<Tank> m_pTank;
};