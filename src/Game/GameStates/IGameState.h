#ifndef _IGAMESTATE_H
#define _IGAMESTATE_H 1.0

class IGameState {
public:
  virtual void render() const noexcept = 0;
  virtual void update(const double delta) noexcept = 0;
  virtual ~IGameState() = default;
  virtual unsigned int getStateWidth() const noexcept = 0;
  virtual unsigned int getStateHeight() const noexcept = 0;
};
#endif // !_IGAMESTATE_H