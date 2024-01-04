#ifndef _TIMER_H
#define _TIMER_H 1.0

#include <functional>
class Timer {
public:
	Timer() noexcept;
	void update(const double dellta) noexcept;
	void start(const double duration) noexcept;
	void setCallback(std::function<void()> callback) noexcept;
private:
	std::function<void()> m_callback;
	double m_timeLeft;
	bool m_isRunning;
};
#endif // !_TIMER_H