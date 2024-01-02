#ifndef _LEVEL_H
#define _LEVEL_H 1.0

#include <string>
#include <vector>
#include <memory>
class IGameObject;

class Level {
public:
	Level(const std::vector<std::string> &levelDescription) noexcept;
	void render() const noexcept;
	void update(const uint64_t delta) noexcept;
private:
	size_t m_width;
	size_t m_height;

	std::vector<std::shared_ptr<IGameObject>> m_mapObjects;
};
#endif // !_LEVEL_H