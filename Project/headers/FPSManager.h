#pragma once

#include "Stopwatch.h"

class FPSManager
{
public:

	FPSManager() = default;

	void startFrame();
	void endFrame();

	static const double& getFps();
	const Stopwatch& getTimer() const;

private:

	double calculateFps(const double& timeElapsed);

	static double __applicationFPS;

	Stopwatch m_Timer;

};

