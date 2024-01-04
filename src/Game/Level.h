#ifndef _LEVEL_H
#define _LEVEL_H 1.0

#include <string>
#include <vector>
#include <memory>

#include <glm/vec2.hpp>

class IGameObject;

class Level {
public:
	static constexpr unsigned int BLOCK_SIZE = 16;

	Level(const std::vector<std::string> &levelDescription) noexcept;
	void render() const noexcept;
	void update(const uint64_t delta) noexcept;
	size_t getLevelWidth() const noexcept;
	size_t getLevelHeight() const noexcept;

	const glm::ivec2 &getPlayerRespawn_1() const noexcept;
	const glm::ivec2 &getPlayerRespawn_2() const noexcept;
	const glm::ivec2 &getEnemyRespawn_1() const noexcept;
	const glm::ivec2 &getEnemyRespawn_2() const noexcept;
	const glm::ivec2 &getEnemyRespawn_3() const noexcept;
private:
	size_t m_width;
	size_t m_height;

	glm::ivec2 m_playerRespawn_1;
	glm::ivec2 m_playerRespawn_2;
	glm::ivec2 m_enemyRespawn_1;
	glm::ivec2 m_enemyRespawn_2;
	glm::ivec2 m_enemyRespawn_3;

	std::vector<std::shared_ptr<IGameObject>> m_levelObjects;
};
#endif // !_LEVEL_H