#pragma once

class IGameState {
public:
  virtual void render() const noexcept = 0;
  virtual void update(const double delta) noexcept = 0;
  virtual void processInput(const std::array<bool, 349> &aKeys) noexcept {};
  virtual ~IGameState() = default;
  virtual unsigned int getStateWidth() const noexcept = 0;
  virtual unsigned int getStateHeight() const noexcept = 0;
};