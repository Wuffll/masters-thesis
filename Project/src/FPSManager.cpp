#include "FPSManager.h"

#include "Debug.h"

double FPSManager::__applicationFPS = 0.0;

void FPSManager::startFrame()
{
    m_Timer.start();
}

void FPSManager::endFrame()
{
    m_Timer.stop();

    __applicationFPS = calculateFps(m_Timer.getTimeElapsed());
}

const double& FPSManager::getFps()
{
    return __applicationFPS;
}

const Stopwatch& FPSManager::getTimer() const
{
    return m_Timer;
}

double FPSManager::calculateFps(const double& timeElapsed)
{
    return 1.0 / timeElapsed;
}
