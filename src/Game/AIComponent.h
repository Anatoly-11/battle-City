#pragma once

class Tank;

class AIComponent {
public:
  AIComponent(Tank *pParentTank) noexcept;
  void update(const double delta) noexcept;
  ~AIComponent() noexcept;
private:
  Tank *m_pParentTank;
};