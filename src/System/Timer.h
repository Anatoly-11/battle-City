#pragma once

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