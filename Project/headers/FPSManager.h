#pragma once

#include "Stopwatch.h"

class FPSManager
{
public:

	FPSManager() = default;
	FPSManager(float targetFps);

	void startFrame();
	void endFrame();

	static const double& getFps();
	
	const float& getFrameTime() const;

	void setTargetFps(float targetFps);

private:

	double calculateFps(const double& timeElapsed);

	static double __applicationFPS;

	Stopwatch m_Timer;
	float m_TargetFps = 60.0f;

};

