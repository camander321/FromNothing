#include "Timer.h"


Timer::Timer()
{
	currentPoint = std::chrono::high_resolution_clock::now();
	lastPoint = currentPoint;
	deltaTime = 0;
}


void Timer::updateDelta()
{
	lastPoint = currentPoint;
	currentPoint = std::chrono::high_resolution_clock::now();
	deltaTime = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(currentPoint - lastPoint).count();
}

double Timer::getDelta()
{
	return deltaTime;
}

double Timer::getCurrentDelta()
{
	return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - lastPoint).count();
}
