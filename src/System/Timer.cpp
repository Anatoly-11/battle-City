#include "Timer.h"

Timer::Timer() noexcept : m_timeLeft(0), m_isRunning(false) {

}

void Timer::update(const double dellta) noexcept {
  if(m_isRunning) {
    m_timeLeft -= dellta;
    if(m_timeLeft <= 0.0) {
      m_timeLeft = 0;
      m_isRunning = false;
      m_callback();
    }
  }
}

void Timer::start(const double duration) noexcept {
  m_timeLeft = duration;
  m_isRunning = true;
}

void Timer::setCallback(std::function<void()> callback) noexcept {
  m_callback = callback;
}