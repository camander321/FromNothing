#pragma once

#include <chrono>

class Timer
{
public:
	const double SECOND = 1000000000.0;

	Timer();
	void updateDelta();
	double getDelta();
	double getCurrentDelta();

private:
	std::chrono::steady_clock::time_point currentPoint;
	std::chrono::steady_clock::time_point lastPoint;

	double deltaTime;
};

