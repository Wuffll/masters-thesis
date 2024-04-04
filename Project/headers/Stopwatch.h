#pragma once

#include <chrono>

#define CLOCK std::chrono::high_resolution_clock

class Stopwatch
{
public:

	Stopwatch() = default;

	void start();
	const double& stop();
	const double& lap();

	const bool& hasStarted() const;

	const double& getTimeElapsed() const;

private:

	bool m_HasStarted = false;

	std::chrono::time_point<CLOCK> m_Start;
	std::chrono::time_point<CLOCK> m_End;

	double m_TimeElapsed = 0.0; // in seconds

};

